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

    namespace cms = cucumber::messages;

    using table_rows = std::vector<std::shared_ptr<cms::TableRow>>;
    using tags = std::vector<std::shared_ptr<cms::Tag>>;
    using comments = std::vector<std::shared_ptr<cms::Comment>>;

    class AstBuilder
    {
    public:
        using result_type = cms::GherkinDocument;

        AstBuilder();
        AstBuilder(id_generator_ptr idp);

        virtual ~AstBuilder();

        void reset(std::string_view uri);

        void start_rule(RuleType RuleType);
        void end_rule(RuleType RuleType);
        void build(const Token& token);

        const cms::GherkinDocument& get_result() const;

    private:
        using ast_node_stack = std::stack<AstNode>;

        std::string next_id();

        void transform_node(AstNode& from, AstNode& destination);

        cms::Step make_step(AstNode& node);
        cms::DocString make_doc_string(AstNode& node);
        cms::DataTable make_data_table(AstNode& node);
        cms::Background make_background(AstNode& node);
        cms::Scenario make_scenario_definition(AstNode& node);
        cms::Examples make_examples_definition(AstNode& node);
        table_rows make_examples_table(AstNode& node);
        std::string make_description(AstNode& node);
        cms::Feature make_feature(AstNode& node);
        cms::Rule make_rule(AstNode& node);
        cms::GherkinDocument make_gherkin_document(AstNode& node);

        std::shared_ptr<cms::Location> get_location(const Token& token, std::size_t column = 0) const;

        table_rows get_table_rows(const AstNode& node);
        void ensure_cell_count(const table_rows& rows) const;
        table_cells get_table_cells(const Token& token);
        tags get_tags(const AstNode& node);

        AstNode pop_node();
        AstNode& current_node();
        const AstNode& current_node() const;

        id_generator_ptr idp_;
        ast_node_stack stack_;
        std::string_view uri_;
        comments comments_;
        cms::GherkinDocument doc_;
    };

    using ast_builder_ptr = std::unique_ptr<AstBuilder>;

    template<typename... Args>
    ast_builder_ptr new_ast_builder(Args&&... args)
    {
        return std::make_unique<AstBuilder>(std::forward<Args>(args)...);
    }

}

#endif
