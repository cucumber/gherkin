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

    AstBuilder::AstBuilder(IdGeneratorPtr idp)
        : idp(std::move(std::move(idp)))
    {}

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
            messages::Comment comment{ GetLocation(token), token.matchedText };

            comments.emplace_back(std::make_shared<messages::Comment>(std::move(comment)));
        }
        else
        {
            CurrentNode().Add(token.matchedType, token);
        }
    }

    const messages::GherkinDocument& AstBuilder::GetResult() const
    {
        const auto* document = CurrentNode().GetSingle<messages::GherkinDocument>(RuleType::gherkinDocument);

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

    messages::Step AstBuilder::MakeStep(AstNode& node)
    {
        const auto& stepLine = node.GetToken(RuleType::stepLine);

        messages::Step step{ GetLocation(stepLine), stepLine.matchedKeyword.value_or(""), stepLine.matchedKeywordType, stepLine.matchedText, std::nullopt, std::nullopt, NextId() };

        node.Set(RuleType::docString, step.docString);
        node.Set(RuleType::dataTable, step.dataTable);

        return step;
    }

    messages::DocString AstBuilder::MakeDocString(AstNode& node)
    {
        const auto& Tokens = node.GetTokens(RuleType::docStringSeparator);
        const auto& separatorToken = Tokens[0];

        StringViews lineViews;

        for (const auto& tok : node.GetTokens(RuleType::other))
        {
            lineViews.emplace_back(tok.matchedText);
        }

        auto content = Join("\n", lineViews);

        messages::DocString docString{ GetLocation(separatorToken), std::nullopt, content, separatorToken.matchedKeyword.value_or("") };

        if (!separatorToken.matchedText.empty())
        {
            docString.mediaType = separatorToken.matchedText;
        }

        return docString;
    }

    messages::DataTable AstBuilder::MakeDataTable(AstNode& node)
    {
        auto rows = GetTableRows(node);

        messages::DataTable dataTable;
        dataTable.rows = std::move(rows);

        if (!dataTable.rows.empty() && dataTable.rows.front()->location)
        {
            dataTable.location = dataTable.rows.front()->location;
        }

        return dataTable;
    }

    messages::Background AstBuilder::MakeBackground(AstNode& node)
    {
        const auto& backgroundLine = node.GetToken(RuleType::backgroundLine);

        messages::Background background{ GetLocation(backgroundLine), backgroundLine.matchedKeyword.value_or(""), backgroundLine.matchedText, {}, {}, NextId() };

        node.Set(RuleType::description, background.description);
        node.Set(RuleType::step, background.steps);

        return background;
    }

    messages::Scenario AstBuilder::MakeScenarioDefinition(AstNode& node)
    {
        const auto* pnode = node.GetSingle<AstNode>(RuleType::scenario);
        const auto& scenarioNode = *pnode;
        const auto& scenarioLine = scenarioNode.GetToken(RuleType::scenarioLine);

        messages::Scenario scenario{ GetLocation(scenarioLine), GetTags(node), scenarioLine.matchedKeyword.value_or(""), scenarioLine.matchedText, {}, {}, {}, NextId() };

        scenarioNode.Set(RuleType::description, scenario.description);
        scenarioNode.Set(RuleType::step, scenario.steps);
        scenarioNode.Set(RuleType::examplesDefinition, scenario.examples);

        return scenario;
    }

    messages::Examples AstBuilder::MakeExamplesDefinition(AstNode& node)
    {
        const auto* pnode = node.GetSingle<AstNode>(RuleType::examples);
        const auto& examplesNode = *pnode;
        const auto& examplesLine = examplesNode.GetToken(RuleType::examplesLine);

        messages::Examples examples{ GetLocation(examplesLine), GetTags(node), examplesLine.matchedKeyword.value_or(""), examplesLine.matchedText, {}, std::nullopt, {}, NextId() };

        examplesNode.Set(RuleType::description, examples.description);

        const auto* prows = examplesNode.GetSingle<TableRows>(RuleType::examplesTable);

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

    TableRows AstBuilder::MakeExamplesTable(AstNode& node)
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

        StringViews descriptionLines;

        for (std::size_t i = 0; i < ntoks; ++i)
        {
            descriptionLines.emplace_back(toks[i].matchedText);
        }

        return Join("\n", descriptionLines);
    }

    messages::Feature AstBuilder::MakeFeature(AstNode& node)
    {
        const auto* pnode = node.GetSingle<AstNode>(RuleType::featureHeader);
        const auto& header = *pnode;

        const auto* ptoken = header.GetSingle<Token>(RuleType::featureLine);
        const auto& featureLine = *ptoken;

        messages::Feature feature{ GetLocation(featureLine), GetTags(header), featureLine.matchedGherkinDialect, featureLine.matchedKeyword.value_or(""), featureLine.matchedText };

        header.Set(RuleType::description, feature.description);

        const auto* background = node.GetSingle<messages::Background>(RuleType::background);

        if (background != nullptr)
        {
            messages::FeatureChild child;
            child.background = std::make_shared<messages::Background>(*background);
            feature.children.emplace_back(std::make_shared<messages::FeatureChild>(child));
        }

        const auto* scenarios = node.GetItems<messages::Scenario>(RuleType::scenarioDefinition);

        if (scenarios != nullptr)
        {
            for (const auto& scenario : *scenarios)
            {
                messages::FeatureChild child;
                child.scenario = std::make_shared<messages::Scenario>(scenario);
                feature.children.emplace_back(std::make_shared<messages::FeatureChild>(child));
            }
        }

        const auto* rules = node.GetItems<messages::Rule>(RuleType::rule);

        if (rules != nullptr)
        {
            for (const auto& rule : *rules)
            {
                messages::FeatureChild child;
                child.rule = std::make_shared<messages::Rule>(rule);
                feature.children.emplace_back(std::make_shared<messages::FeatureChild>(child));
            }
        }

        return feature;
    }

    messages::Rule AstBuilder::MakeRule(AstNode& node)
    {
        const auto* pnode = node.GetSingle<AstNode>(RuleType::ruleHeader);
        const auto& header = *pnode;

        const auto* ptoken = header.GetSingle<Token>(RuleType::ruleLine);
        const auto& ruleLine = *ptoken;

        messages::Rule rule{ GetLocation(ruleLine), GetTags(header), ruleLine.matchedKeyword.value_or(""), ruleLine.matchedText, {}, {}, NextId() };

        header.Set(RuleType::description, rule.description);

        const auto* background = node.GetSingle<messages::Background>(RuleType::background);

        if (background != nullptr)
        {
            messages::RuleChild child;
            child.background = std::make_shared<messages::Background>(*background);
            rule.children.emplace_back(std::make_shared<messages::RuleChild>(child));
        }

        const auto* scenarios = node.GetItems<messages::Scenario>(RuleType::scenarioDefinition);

        if (scenarios != nullptr)
        {
            for (const auto& scenario : *scenarios)
            {
                messages::RuleChild child;
                child.scenario = std::make_shared<messages::Scenario>(scenario);
                rule.children.emplace_back(std::make_shared<messages::RuleChild>(child));
            }
        }

        return rule;
    }

    messages::GherkinDocument AstBuilder::MakeGherkinDocument(AstNode& node)
    {
        messages::GherkinDocument document{ std::string(uri), std::nullopt, comments };

        node.Set(RuleType::feature, document.feature);

        return document;
    }

    std::shared_ptr<messages::Location> AstBuilder::GetLocation(const Token& token, std::size_t column)
    {
        std::size_t col = column == 0 ? token.location.column.value_or(0) : column;
        return std::make_shared<messages::Location>(messages::Location{ token.location.line, col > 0 ? std::optional(col) : std::nullopt });
    }

    TableRows AstBuilder::GetTableRows(const AstNode& node)
    {
        TableRows rows;

        for (const auto& token : node.GetTokens(RuleType::tableRow))
        {
            auto row = std::make_shared<messages::TableRow>();
            row->location = GetLocation(token);
            row->cells = GetTableCells(token);
            row->id = NextId();
            rows.emplace_back(row);
        }

        EnsureCellCount(rows);

        return rows;
    }

    void AstBuilder::EnsureCellCount(const TableRows& rows)
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
                throw AstBuilderError("inconsistent cell count within the table", { row->location->line, row->location->column.value_or(0) });
            }
        }
    }

    TableCells AstBuilder::GetTableCells(const Token& token)
    {
        TableCells cells;

        for (const auto& cellItem : token.matchedItems)
        {
            auto cell = std::make_shared<messages::TableCell>();
            cell->location = GetLocation(token, cellItem.column);
            cell->value = cellItem.text;
            cells.emplace_back(cell);
        }

        return cells;
    }

    Tags AstBuilder::GetTags(const AstNode& node)
    {
        Tags tagList;

        const auto* pnode = node.GetSingle<AstNode>(RuleType::tags);

        if (pnode != nullptr)
        {
            const auto& tagsNode = *pnode;

            for (const auto& token : tagsNode.GetTokens(RuleType::tagLine))
            {
                for (const auto& tagItem : token.matchedItems)
                {
                    messages::Tag tag{ GetLocation(token, tagItem.column), tagItem.text, NextId() };

                    tagList.emplace_back(std::make_shared<messages::Tag>(std::move(tag)));
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
