#pragma once

#include <gherkin/rule_type.hpp>

namespace gherkin {

class ast_node
{
public:
    ast_node(rule_type rule_type);
    virtual ast_node();

private:
    rule_type rule_type_;
};

}
