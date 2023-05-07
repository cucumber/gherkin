#pragma once

#include <memory>
#include <stack>
#include <vector>

#include <gherkin/token.hpp>
#include <gherkin/rule_type.hpp>
#include <gherkin/ast_node.hpp>

namespace gherkin {

namespace cms = cucumber::messages;
using table_rows = std::vector<cms::table_row>;
using table_cells = std::vector<cms::table_cell>;

class ast_builder
{
public:
    ast_builder();
    virtual ~ast_builder();

    void reset();

    void start_rule(rule_type rule_type);
    void end_rule(rule_type rule_type);
    void build(token& token);

private:
    using ast_node_stack = std::stack<ast_node>;

    std::string next_id();

    node_item transform_node(ast_node& node);

    cms::location get_location(
        const token& token,
        std::size_t column = 0
    ) const;

    table_rows get_table_rows(ast_node& node);
    table_cells get_table_cells(const token& token);

    ast_node pop_node();
    ast_node& current_node();
    const ast_node& current_node() const;

    std::size_t id_counter_ = 0;
    ast_node_stack stack_;
    std::string uri_;
};

using ast_builder_ptr = std::unique_ptr<ast_builder>;

template <typename... Args>
ast_builder_ptr
new_ast_builder(Args&&... args)
{ return std::make_unique<ast_builder>(std::forward<Args>(args)...); }

}
