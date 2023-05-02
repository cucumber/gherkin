#pragma once

#include <memory>

#include <gherkin/token.hpp>
#include <gherkin/rule_type.hpp>

namespace gherkin {

class ast_builder
{
public:
    ast_builder();
    virtual ~ast_builder();

    void reset();

    void build(token& token);
    void start_rule(rule_type rule_type);
    void end_rule(rule_type rule_type);

private:
};

using ast_builder_ptr = std::unique_ptr<ast_builder>;

template <typename... Args>
ast_builder_ptr
new_ast_builder(Args&&... args)
{ return std::make_unique<ast_builder>(std::forward<Args>(args)...); }

}
