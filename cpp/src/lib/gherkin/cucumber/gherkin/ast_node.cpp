#include <cucumber/gherkin/ast_node.hpp>

namespace cucumber::gherkin {

ast_node::ast_node(rule_type rule_type)
: rule_type_(rule_type)
{}

ast_node::ast_node(const ast_node& other)
: rule_type_(other.rule_type_),
sub_items_(other.sub_items_)
{}

ast_node::ast_node(ast_node&& other)
: rule_type_(std::move(other.rule_type_)),
sub_items_(std::move(other.sub_items_))
{}

ast_node::~ast_node()
{}

ast_node&
ast_node::operator=(const ast_node& other)
{
    rule_type_ = other.rule_type_;
    sub_items_ = other.sub_items_;

    return *this;
}

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

}
