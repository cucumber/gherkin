#include "cucumber/gherkin/ast_builder.hpp"
#include "cucumber/gherkin/ast_node.hpp"
#include "cucumber/gherkin/exceptions.hpp"
#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/join_utils.hpp"
#include "cucumber/gherkin/msg_types.hpp"
#include "cucumber/gherkin/regex.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/types.hpp"
#include "cucumber/messages/Background.hpp"
#include "cucumber/messages/Comment.hpp"
#include "cucumber/messages/DataTable.hpp"
#include "cucumber/messages/DocString.hpp"
#include "cucumber/messages/Examples.hpp"
#include "cucumber/messages/Feature.hpp"
#include "cucumber/messages/FeatureChild.hpp"
#include "cucumber/messages/GherkinDocument.hpp"
#include "cucumber/messages/Location.hpp"
#include "cucumber/messages/Rule.hpp"
#include "cucumber/messages/RuleChild.hpp"
#include "cucumber/messages/Scenario.hpp"
#include "cucumber/messages/Step.hpp"
#include "cucumber/messages/TableCell.hpp"
#include "cucumber/messages/TableRow.hpp"
#include "cucumber/messages/Tag.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <optional>
#include <regex>
#include <string>
#include <string_view>
#include <utility>

namespace cucumber::gherkin
{

    AstBuilder::AstBuilder()
        : AstBuilder(NewIdGenerator())
    {}

    AstBuilder::AstBuilder(id_generator_ptr idp)
        : idp(std::move(std::move(idp)))
    {}

    AstBuilder::~AstBuilder() = default;

    void AstBuilder::Reset(std::string_view uri)
    {
        stack = {};
        stack.emplace(RuleType::none);
        comments.clear();
        this->uri = uri;
    }

    void AstBuilder::StartRule(RuleType ruleType)
    {
        stack.emplace(ruleType);
    }

    void AstBuilder::EndRule([[maybe_unused]] RuleType ruleType)
    {
        auto node = PopNode();

        TransformNode(node, CurrentNode());
    }

    void AstBuilder::Build(const Token& token)
    {
        if (token.matchedType == RuleType::comment)
        {
            cucumber::messages::Comment comment{ GetLocation(token), token.matchedText };

            comments.emplace_back(std::make_shared<cucumber::messages::Comment>(std::move(comment)));
        }
        else
        {
            CurrentNode().Add(token.matchedType, token);
        }
    }

    const cucumber::messages::GherkinDocument& AstBuilder::GetResult() const
    {
        const auto* document = CurrentNode().GetSingle<cucumber::messages::GherkinDocument>(RuleType::gherkinDocument);

        return (document != nullptr) ? *document : doc;
    };

    std::string AstBuilder::NextId()
    {
        return idp->NextId();
    }

    void AstBuilder::TransformNode(AstNode& from, AstNode& destination)
    {
        if (from.Is(RuleType::step))
        {
            destination.Add(from.Type(), MakeStep(from));
        }
        else if (from.Is(RuleType::docString))
        {
            destination.Add(from.Type(), MakeDocString(from));
        }
        else if (from.Is(RuleType::dataTable))
        {
            destination.Add(from.Type(), MakeDataTable(from));
        }
        else if (from.Is(RuleType::background))
        {
            destination.Add(from.Type(), MakeBackground(from));
        }
        else if (from.Is(RuleType::scenarioDefinition))
        {
            destination.Add(from.Type(), MakeScenarioDefinition(from));
        }
        else if (from.Is(RuleType::examplesDefinition))
        {
            destination.Add(from.Type(), MakeExamplesDefinition(from));
        }
        else if (from.Is(RuleType::examplesTable))
        {
            destination.Add(from.Type(), MakeExamplesTable(from));
        }
        else if (from.Is(RuleType::description))
        {
            destination.Add(from.Type(), MakeDescription(from));
        }
        else if (from.Is(RuleType::feature))
        {
            destination.Add(from.Type(), MakeFeature(from));
        }
        else if (from.Is(RuleType::rule))
        {
            destination.Add(from.Type(), MakeRule(from));
        }
        else if (from.Is(RuleType::gherkinDocument))
        {
            destination.Add(from.Type(), MakeGherkinDocument(from));
        }
        else
        {
            destination.Add(from.Type(), from);
        }
    }

    cucumber::messages::Step AstBuilder::MakeStep(AstNode& node)
    {
        const auto& stepLine = node.GetToken(RuleType::stepLine);

        cucumber::messages::Step step{ GetLocation(stepLine), stepLine.matchedKeyword.value_or(""), stepLine.matchedKeywordType, stepLine.matchedText, std::nullopt, std::nullopt, NextId() };

        node.Set(RuleType::docString, step.docString);
        node.Set(RuleType::dataTable, step.dataTable);

        return step;
    }

    cucumber::messages::DocString AstBuilder::MakeDocString(AstNode& node)
    {
        const auto& tokens = node.GetTokens(RuleType::docStringSeparator);
        const auto& separatorToken = tokens[0];

        string_views lineViews;

        for (const auto& tok : node.GetTokens(RuleType::other))
        {
            lineViews.emplace_back(tok.matchedText);
        }

        auto content = Join("\n", lineViews);

        cucumber::messages::DocString docString{ GetLocation(separatorToken), std::nullopt, content, separatorToken.matchedKeyword.value_or("") };

        if (!separatorToken.matchedText.empty())
        {
            docString.mediaType = separatorToken.matchedText;
        }

        return docString;
    }

    cucumber::messages::DataTable AstBuilder::MakeDataTable(AstNode& node)
    {
        auto rows = GetTableRows(node);

        cucumber::messages::DataTable dataTable;
        dataTable.rows = std::move(rows);

        if (!dataTable.rows.empty() && dataTable.rows.front()->location)
        {
            dataTable.location = dataTable.rows.front()->location;
        }

        return dataTable;
    }

    cucumber::messages::Background AstBuilder::MakeBackground(AstNode& node)
    {
        const auto& backgroundLine = node.GetToken(RuleType::backgroundLine);

        cucumber::messages::Background background{ GetLocation(backgroundLine), backgroundLine.matchedKeyword.value_or(""), backgroundLine.matchedText, {}, {}, NextId() };

        node.Set(RuleType::description, background.description);
        node.Set(RuleType::step, background.steps);

        return background;
    }

    cucumber::messages::Scenario AstBuilder::MakeScenarioDefinition(AstNode& node)
    {
        const auto* pnode = node.GetSingle<AstNode>(RuleType::scenario);
        const auto& scenarioNode = *pnode;
        const auto& scenarioLine = scenarioNode.GetToken(RuleType::scenarioLine);

        cucumber::messages::Scenario scenario{ GetLocation(scenarioLine), GetTags(node), scenarioLine.matchedKeyword.value_or(""), scenarioLine.matchedText, {}, {}, {}, NextId() };

        scenarioNode.Set(RuleType::description, scenario.description);
        scenarioNode.Set(RuleType::step, scenario.steps);
        scenarioNode.Set(RuleType::examplesDefinition, scenario.examples);

        return scenario;
    }

    cucumber::messages::Examples AstBuilder::MakeExamplesDefinition(AstNode& node)
    {
        const auto* pnode = node.GetSingle<AstNode>(RuleType::examples);
        const auto& examplesNode = *pnode;
        const auto& examplesLine = examplesNode.GetToken(RuleType::examplesLine);

        cucumber::messages::Examples examples{ GetLocation(examplesLine), GetTags(node), examplesLine.matchedKeyword.value_or(""), examplesLine.matchedText, {}, std::nullopt, {}, NextId() };

        examplesNode.Set(RuleType::description, examples.description);

        const auto* prows = examplesNode.GetSingle<table_rows>(RuleType::examplesTable);

        if (prows != nullptr)
        {
            const auto& rows = *prows;

            examples.tableHeader = rows.front();

            if (rows.size() > 1)
            {
                std::copy(rows.begin() + 1, rows.end(), std::back_inserter(examples.tableBody));
            }
        }

        return examples;
    }

    table_rows AstBuilder::MakeExamplesTable(AstNode& node)
    {
        return GetTableRows(node);
    }

    std::string AstBuilder::MakeDescription(AstNode& node)
    {
        static const std::regex onlySpaces("\\s*");
        auto toks = node.GetTokens(RuleType::other);
        std::size_t ntoks = toks.size();

        while ((ntoks != 0U) && FullMatch(toks[ntoks - 1].matchedText, onlySpaces))
        {
            --ntoks;
        }

        string_views descriptionLines;

        for (std::size_t i = 0; i < ntoks; ++i)
        {
            descriptionLines.emplace_back(toks[i].matchedText);
        }

        return Join("\n", descriptionLines);
    }

    cucumber::messages::Feature AstBuilder::MakeFeature(AstNode& node)
    {
        const auto* pnode = node.GetSingle<AstNode>(RuleType::featureHeader);
        const auto& header = *pnode;

        const auto* ptoken = header.GetSingle<Token>(RuleType::featureLine);
        const auto& featureLine = *ptoken;

        cucumber::messages::Feature feature{ GetLocation(featureLine), GetTags(header), featureLine.matchedGherkinDialect, featureLine.matchedKeyword.value_or(""), featureLine.matchedText };

        header.Set(RuleType::description, feature.description);

        const auto* background = node.GetSingle<cucumber::messages::Background>(RuleType::background);

        if (background != nullptr)
        {
            cucumber::messages::FeatureChild child;
            child.background = std::make_shared<cucumber::messages::Background>(*background);
            feature.children.emplace_back(std::make_shared<cucumber::messages::FeatureChild>(child));
        }

        const auto* scenarios = node.GetItems<cucumber::messages::Scenario>(RuleType::scenarioDefinition);

        if (scenarios != nullptr)
        {
            for (const auto& scenario : *scenarios)
            {
                cucumber::messages::FeatureChild child;
                child.scenario = std::make_shared<cucumber::messages::Scenario>(scenario);
                feature.children.emplace_back(std::make_shared<cucumber::messages::FeatureChild>(child));
            }
        }

        const auto* rules = node.GetItems<cucumber::messages::Rule>(RuleType::rule);

        if (rules != nullptr)
        {
            for (const auto& rule : *rules)
            {
                cucumber::messages::FeatureChild child;
                child.rule = std::make_shared<cucumber::messages::Rule>(rule);
                feature.children.emplace_back(std::make_shared<cucumber::messages::FeatureChild>(child));
            }
        }

        return feature;
    }

    cucumber::messages::Rule AstBuilder::MakeRule(AstNode& node)
    {
        const auto* pnode = node.GetSingle<AstNode>(RuleType::ruleHeader);
        const auto& header = *pnode;

        const auto* ptoken = header.GetSingle<Token>(RuleType::ruleLine);
        const auto& ruleLine = *ptoken;

        cucumber::messages::Rule rule{ GetLocation(ruleLine), GetTags(header), ruleLine.matchedKeyword.value_or(""), ruleLine.matchedText, {}, {}, NextId() };

        header.Set(RuleType::description, rule.description);

        const auto* background = node.GetSingle<cucumber::messages::Background>(RuleType::background);

        if (background != nullptr)
        {
            cucumber::messages::RuleChild child;
            child.background = std::make_shared<cucumber::messages::Background>(*background);
            rule.children.emplace_back(std::make_shared<cucumber::messages::RuleChild>(child));
        }

        const auto* scenarios = node.GetItems<cucumber::messages::Scenario>(RuleType::scenarioDefinition);

        if (scenarios != nullptr)
        {
            for (const auto& scenario : *scenarios)
            {
                cucumber::messages::RuleChild child;
                child.scenario = std::make_shared<cucumber::messages::Scenario>(scenario);
                rule.children.emplace_back(std::make_shared<cucumber::messages::RuleChild>(child));
            }
        }

        return rule;
    }

    cucumber::messages::GherkinDocument AstBuilder::MakeGherkinDocument(AstNode& node)
    {
        cucumber::messages::GherkinDocument document{ std::string(uri), std::nullopt, comments };

        node.Set(RuleType::feature, document.feature);

        return document;
    }

    std::shared_ptr<cucumber::messages::Location> AstBuilder::GetLocation(const Token& token, std::size_t column)
    {
        std::size_t col = column == 0 ? token.location.column.value_or(0) : column;
        return std::make_shared<cucumber::messages::Location>(cucumber::messages::Location{ token.location.line, col > 0 ? std::optional(col) : std::nullopt });
    }

    table_rows AstBuilder::GetTableRows(const AstNode& node)
    {
        table_rows rows;

        for (const auto& token : node.GetTokens(RuleType::tableRow))
        {
            auto row = std::make_shared<cucumber::messages::TableRow>();
            row->location = GetLocation(token);
            row->cells = GetTableCells(token);
            row->id = NextId();
            rows.emplace_back(row);
        }

        EnsureCellCount(rows);

        return rows;
    }

    void AstBuilder::EnsureCellCount(const table_rows& rows)
    {
        if (rows.empty())
        {
            return;
        }

        std::size_t const cellCount = rows.front()->cells.size();

        for (const auto& row : rows)
        {
            if (row->cells.size() != cellCount)
            {
                throw ast_builder_error("inconsistent cell count within the table", { row->location->line, row->location->column.value_or(0) });
            }
        }
    }

    table_cells AstBuilder::GetTableCells(const Token& token)
    {
        table_cells cells;

        for (const auto& cellItem : token.matchedItems)
        {
            auto cell = std::make_shared<cucumber::messages::TableCell>();
            cell->location = GetLocation(token, cellItem.column);
            cell->value = cellItem.text;
            cells.emplace_back(cell);
        }

        return cells;
    }

    tags AstBuilder::GetTags(const AstNode& node)
    {
        tags tagList;

        const auto* pnode = node.GetSingle<AstNode>(RuleType::tags);

        if (pnode != nullptr)
        {
            const auto& tagsNode = *pnode;

            for (const auto& token : tagsNode.GetTokens(RuleType::tagLine))
            {
                for (const auto& tagItem : token.matchedItems)
                {
                    cucumber::messages::Tag tag{ GetLocation(token, tagItem.column), tagItem.text, NextId() };

                    tagList.emplace_back(std::make_shared<cucumber::messages::Tag>(std::move(tag)));
                }
            }
        }

        return tagList;
    }

    AstNode AstBuilder::PopNode()
    {
        AstNode poppedNode = std::move(CurrentNode());

        stack.pop();

        return poppedNode;
    }

    AstNode& AstBuilder::CurrentNode()
    {
        return stack.top();
    }

    const AstNode& AstBuilder::CurrentNode() const
    {
        return stack.top();
    }

}
