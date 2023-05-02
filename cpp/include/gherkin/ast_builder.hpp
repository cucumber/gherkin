#pragma once

#include <memory>

#include <gherkin/token.hpp>

namespace gherkin {

class ast_builder
{
public:
    ast_builder();
    virtual ~ast_builder();

    void reset();

    void build(token& token);

private:
};

using ast_builder_ptr = std::unique_ptr<ast_builder>;

template <typename... Args>
ast_builder_ptr
new_ast_builder(Args&&... args)
{ return std::make_unique<ast_builder>(std::forward<Args>(args)...); }

}
