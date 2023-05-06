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
ast_node::add(rule_type rt, node_item&& n)
{ sub_items_[rt].emplace_back(std::move(n)); }

const node_item&
ast_node::get_single(rule_type rule_type) const
{
    auto it = sub_items_.find(rule_type);

    if (it != sub_items_.end()) {
        const auto& msgs = it->second;

        if (!msgs.empty()) {
            return msgs.front();
        }
    }

    return empty_node_item_;
}

const node_items&
ast_node::get_items(rule_type rule_type) const
{
    auto it = sub_items_.find(rule_type);

    return
        it != sub_items_.end()
        ? it->second
        : empty_node_items_
        ;
}

const token&
ast_node::get_token(rule_type rule_type) const
{ return std::get<token>(get_single(rule_type)); }

const node_items&
ast_node::get_tokens(rule_type rule_type) const
{ return get_items(rule_type); }

}
