#ifndef CUCUMBER_GHERKIN_BUILDER_HPP
#define CUCUMBER_GHERKIN_BUILDER_HPP

#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include <memory>
#include <string>

namespace cucumber::gherkin
{

    template<typename T>
    struct Builder
    {
        using result_type = T;

        virtual void reset(const std::string& uri = "")
        {}

        virtual void start_rule(RuleType RuleType)
        {}

        virtual void end_rule(RuleType RuleType)
        {}

        virtual void build(const Token& token)
        {}

        result_type get_result() const
        {
            return {};
        }
    };

    template<typename T>
    using builder_ptr = std::unique_ptr<Builder<T>>;

    template<typename Builder, typename T, typename... Args>
    builder_ptr<T> new_builder(Args&&... args)
    {
        return std::make_unique<Builder>(std::forward<Args>(args)...);
    }

}

#endif
