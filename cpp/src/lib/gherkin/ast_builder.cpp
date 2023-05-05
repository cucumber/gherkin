#include <cucumber/messages/step.hpp>

#include <gherkin/ast_builder.hpp>

namespace gherkin {

ast_builder::ast_builder()
{}

ast_builder::~ast_builder()
{}

void
ast_builder::reset()
{}

void
ast_builder::start_rule(rule_type rule_type)
{ stack_.emplace(rule_type); }

void
ast_builder::end_rule(rule_type rule_type)
{
    auto n = pop_node();
    auto rt = n.type();
    auto p = transform_node(n);

    current_node().add(rt, std::move(p));
}

void
build(token& token)
{}

message
ast_builder::transform_node(ast_node& node)
{
    if (node.is(rule_type::step)) {
        cucumber::messages::step s{{}, {"titi"}, "toto"};
    }

    return {};
}

ast_node
ast_builder::pop_node()
{
    ast_node n = std::move(current_node());

    stack_.pop();

    return n;
}

ast_node&
ast_builder::current_node()
{ return stack_.top(); }

const ast_node&
ast_builder::current_node() const
{ return stack_.top(); }

}
