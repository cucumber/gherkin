#ifndef CUCUMBER_GHERKIN_AST_BUILDER_HPP
#define CUCUMBER_GHERKIN_AST_BUILDER_HPP

#include "cucumber/gherkin/ast_node.hpp"
#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/msg_types.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/messages/All.hpp"
#include <cstddef>
#include <memory>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

namespace cucumber::gherkin
{
    using TableRows = std::vector<std::shared_ptr<messages::TableRow>>;
    using Tags = std::vector<std::shared_ptr<messages::Tag>>;
    using Comments = std::vector<std::shared_ptr<messages::Comment>>;

    class AstBuilder
    {
    public:
        using ResultType = messages::GherkinDocument;

        AstBuilder();
        AstBuilder(IdGeneratorPtr idp);

        virtual ~AstBuilder() = default;
        AstBuilder(const AstBuilder&) = delete;
        AstBuilder& operator=(const AstBuilder&) = delete;
        AstBuilder(AstBuilder&&) = delete;
        AstBuilder& operator=(AstBuilder&&) = delete;

        void Reset(std::string_view uri);

        void StartRule(RuleType ruleType);
        void EndRule(RuleType ruleType);
        void Build(const Token& token);

        [[nodiscard]] const ResultType& GetResult() const;

    private:
        using AstNodeStack = std::stack<AstNode>;

        std::string NextId();

        void TransformNode(AstNode& from, AstNode& destination);

        messages::Step MakeStep(AstNode& node);
        static messages::DocString MakeDocString(AstNode& node);
        messages::DataTable MakeDataTable(AstNode& node);
        messages::Background MakeBackground(AstNode& node);
        messages::Scenario MakeScenarioDefinition(AstNode& node);
        messages::Examples MakeExamplesDefinition(AstNode& node);
        TableRows MakeExamplesTable(AstNode& node);
        static std::string MakeDescription(AstNode& node);
        messages::Feature MakeFeature(AstNode& node);
        messages::Rule MakeRule(AstNode& node);
        ResultType MakeGherkinDocument(AstNode& node);

        static std::shared_ptr<messages::Location> GetLocation(const Token& token, std::size_t column = 0);

        TableRows GetTableRows(const AstNode& node);
        static void EnsureCellCount(const TableRows& rows);
        static TableCells GetTableCells(const Token& token);
        Tags GetTags(const AstNode& node);

        AstNode PopNode();
        AstNode& CurrentNode();
        [[nodiscard]] const AstNode& CurrentNode() const;

        IdGeneratorPtr idp;
        AstNodeStack stack;
        std::string_view uri;
        Comments comments;
        ResultType doc;
    };

    using AstBuilderPtr = std::unique_ptr<AstBuilder>;

    template<typename... Args>
    AstBuilderPtr NewAstBuilder(Args&&... args)
    {
        return std::make_unique<AstBuilder>(std::forward<Args>(args)...);
    }

}

#endif
