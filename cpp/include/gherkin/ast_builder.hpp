#pragma once

#include <memory>
#include <stack>

#include <gherkin/token.hpp>
#include <gherkin/rule_type.hpp>
#include <gherkin/ast_node.hpp>

namespace gherkin {

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

    message transform_node(ast_node& node);

    ast_node pop_node();
    ast_node& current_node();
    const ast_node& current_node() const;

    ast_node_stack stack_;
};

using ast_builder_ptr = std::unique_ptr<ast_builder>;

template <typename... Args>
ast_builder_ptr
new_ast_builder(Args&&... args)
{ return std::make_unique<ast_builder>(std::forward<Args>(args)...); }

}
