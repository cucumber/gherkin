#pragma once

#include <memory>

#include <gherkin/node_item.hpp>

namespace gherkin {

class ast_node
{
public:
    ast_node(rule_type rule_type);
    ast_node(const ast_node& other) = delete;
    ast_node(ast_node&& other);

    virtual ~ast_node();

    ast_node& operator=(const ast_node& other) = delete;
    ast_node& operator=(ast_node&& other);

    bool is(rule_type rule_type) const;

    rule_type type() const;

    void add(rule_type rule_type, node_item&& m);

    const node_item& get_single(rule_type rule_type) const;
    const node_items& get_items(rule_type rule_type) const;
    const token& get_token(rule_type rule_type) const;
    const node_items& get_tokens(rule_type rule_type) const;

private:
    rule_type rule_type_;
    node_items_map sub_items_;
    node_item empty_node_item_;
    node_items empty_node_items_;
};

}
