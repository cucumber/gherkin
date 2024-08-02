#pragma once

#include <memory>
#include <stack>
#include <vector>
#include <string_view>

#include <cucumber/messages/all.hpp>

#include <cucumber/gherkin/token.hpp>
#include <cucumber/gherkin/rule_type.hpp>
#include <cucumber/gherkin/ast_node.hpp>
#include <cucumber/gherkin/id_generator.hpp>

namespace cucumber::gherkin {

namespace cms = cucumber::messages;

using table_rows = std::vector<cms::table_row>;
using table_cells = std::vector<cms::table_cell>;
using tags = std::vector<cms::tag>;
using comments = std::vector<cms::comment>;

class ast_builder
{
public:
    using result_type = cms::gherkin_document;

    ast_builder();
    ast_builder(id_generator_ptr idp);

    virtual ~ast_builder();

    void reset(std::string_view uri);

    void start_rule(rule_type rule_type);
    void end_rule(rule_type rule_type);
    void build(const token& token);

    const cms::gherkin_document& get_result() const;

private:
    using ast_node_stack = std::stack<ast_node>;

    std::string next_id();

    void transform_node(ast_node& from, ast_node& to);

    cms::step make_step(ast_node& node);
    cms::doc_string make_doc_string(ast_node& node);
    cms::data_table make_data_table(ast_node& node);
    cms::background make_background(ast_node& node);
    cms::scenario make_scenario_definition(ast_node& node);
    cms::examples make_examples_definition(ast_node& node);
    table_rows make_examples_table(ast_node& node);
    std::string make_description(ast_node& node);
    cms::feature make_feature(ast_node& node);
    cms::rule make_rule(ast_node& node);
    cms::gherkin_document make_gherkin_document(ast_node& node);

    cms::location get_location(
        const token& token,
        std::size_t column = 0
    ) const;

    table_rows get_table_rows(const ast_node& node);
    void ensure_cell_count(const table_rows& rows) const;
    table_cells get_table_cells(const token& token);
    tags get_tags(const ast_node& node);

    ast_node pop_node();
    ast_node& current_node();
    const ast_node& current_node() const;

    id_generator_ptr idp_;
    ast_node_stack stack_;
    std::string_view uri_;
    comments comments_;
    cms::gherkin_document doc_;
};

using ast_builder_ptr = std::unique_ptr<ast_builder>;

template <typename... Args>
ast_builder_ptr
new_ast_builder(Args&&... args)
{ return std::make_unique<ast_builder>(std::forward<Args>(args)...); }

}
