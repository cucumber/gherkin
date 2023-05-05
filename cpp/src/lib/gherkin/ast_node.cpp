#include <gherkin/ast_node.hpp>

namespace gherkin {

ast_node::ast_node(rule_type rule_type)
: rule_type_(rule_type)
{}

ast_node::ast_node(ast_node&& other)
: rule_type_(std::move(other.rule_type_)),
sub_items_(std::move(other.sub_items_))
{}

ast_node::~ast_node()
{}

ast_node&
ast_node::operator=(ast_node&& other)
{
    rule_type_ = std::move(other.rule_type_);
    sub_items_ = std::move(other.sub_items_);

    return *this;
}

bool
ast_node::is(rule_type rule_type) const
{ return rule_type_ == rule_type; }

rule_type
ast_node::type() const
{ return rule_type_; }

void
ast_node::add(rule_type rt, message&& m)
{ sub_items_[rt].emplace_back(std::move(m)); }

}
