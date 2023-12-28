#pragma once

#include <string>
#include <memory>

#include <cucumber/gherkin/rule_type.hpp>
#include <cucumber/gherkin/token.hpp>

namespace cucumber::gherkin {

template <typename T>
struct builder
{
    using result_type = T;

    virtual void reset(const std::string& uri = "")
    {}

    virtual void start_rule(rule_type rule_type)
    {}

    virtual void end_rule(rule_type rule_type)
    {}

    virtual void build(const token& token)
    {}

    result_type get_result() const
    { return {}; }
};

template <typename T>
using builder_ptr = std::unique_ptr<builder<T>>;

template <
    typename Builder,
    typename T,
    typename... Args
>
builder_ptr<T>
new_builder(Args&&... args)
{ return std::make_unique<Builder>(std::forward<Args>(args)...); }

}
