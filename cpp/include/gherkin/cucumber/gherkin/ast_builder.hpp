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
    using table_rows = std::vector<std::shared_ptr<messages::TableRow>>;
    using Tags = std::vector<std::shared_ptr<messages::Tag>>;
    using Comments = std::vector<std::shared_ptr<messages::Comment>>;

    class AstBuilder
    {
    public:
        using result_type = messages::GherkinDocument;

        AstBuilder();
        AstBuilder(id_generator_ptr idp);

        virtual ~AstBuilder();
        AstBuilder(const AstBuilder&) = delete;
        AstBuilder& operator=(const AstBuilder&) = delete;
        AstBuilder(AstBuilder&&) = delete;
        AstBuilder& operator=(AstBuilder&&) = delete;

        void Reset(std::string_view uri);

        void StartRule(RuleType ruleType);
        void EndRule(RuleType ruleType);
        void Build(const Token& token);

        [[nodiscard]] const result_type& GetResult() const;

    private:
        using ast_node_stack = std::stack<AstNode>;

        std::string NextId();

        void TransformNode(AstNode& from, AstNode& destination);

        messages::Step MakeStep(AstNode& node);
        static messages::DocString MakeDocString(AstNode& node);
        messages::DataTable MakeDataTable(AstNode& node);
        messages::Background MakeBackground(AstNode& node);
        messages::Scenario MakeScenarioDefinition(AstNode& node);
        messages::Examples MakeExamplesDefinition(AstNode& node);
        table_rows MakeExamplesTable(AstNode& node);
        static std::string MakeDescription(AstNode& node);
        messages::Feature MakeFeature(AstNode& node);
        messages::Rule MakeRule(AstNode& node);
        result_type MakeGherkinDocument(AstNode& node);

        static std::shared_ptr<messages::Location> GetLocation(const Token& token, std::size_t column = 0);

        table_rows GetTableRows(const AstNode& node);
        static void EnsureCellCount(const table_rows& rows);
        static TableCells GetTableCells(const Token& token);
        Tags GetTags(const AstNode& node);

        AstNode PopNode();
        AstNode& CurrentNode();
        [[nodiscard]] const AstNode& CurrentNode() const;

        id_generator_ptr idp;
        ast_node_stack stack;
        std::string_view uri;
        Comments comments;
        result_type doc;
    };

    using ast_builder_ptr = std::unique_ptr<AstBuilder>;

    template<typename... Args>
    ast_builder_ptr NewAstBuilder(Args&&... args)
    {
        return std::make_unique<AstBuilder>(std::forward<Args>(args)...);
    }

}

#endif
