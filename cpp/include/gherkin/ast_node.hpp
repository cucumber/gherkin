#pragma once

#include <memory>

#include <gherkin/messages.hpp>

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

    void add(rule_type rt, message&& m);

private:
    rule_type rule_type_;
    messages_map sub_items_;
};

}
