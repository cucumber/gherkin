#ifndef CUCUMBER_GHERKIN_PARSER_BASE_HPP
#define CUCUMBER_GHERKIN_PARSER_BASE_HPP

#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/parser_context.hpp"
#include "cucumber/gherkin/token_matcher.hpp"
#include "cucumber/gherkin/token_scanner.hpp"
#include <cucumber/messages/GherkinDocument.hpp>
#include <string_view>
#include <utility>

namespace cucumber::gherkin
{
    template<typename BuilderType>
    class ParserBase
    {
    public:
        using result_type = typename BuilderType::result_type;
        using context_type = ParserContext<BuilderType>;

        ParserBase() = default;
        explicit ParserBase(id_generator_ptr idp);

        virtual ~ParserBase() = default;
        ParserBase(const ParserBase&) = delete;
        ParserBase& operator=(const ParserBase&) = delete;
        ParserBase(ParserBase&&) = delete;
        ParserBase& operator=(ParserBase&&) = delete;

        result_type Parse(std::string_view uri, std::string_view data);

    protected:
        void Reset(std::string_view uri, std::string_view data);

        result_type GetResult() const;

        virtual void parse(context_type& context) = 0;

        BuilderType builder;  // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
        TokenScanner scanner; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
        TokenMatcher matcher; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
    };

    template<typename BuilderType>
    ParserBase<BuilderType>::ParserBase(id_generator_ptr idp)
        : builder{ std::move(idp) }
    {}

    template<typename BuilderType>
    auto ParserBase<BuilderType>::Parse(std::string_view uri, std::string_view data) -> result_type
    {
        Reset(uri, data);

        context_type context{ builder, scanner, matcher };

        parse(context);

        return GetResult();
    }

    template<typename BuilderType>
    auto ParserBase<BuilderType>::Reset(std::string_view uri, std::string_view data) -> void // NOLINT(bugprone-easily-swappable-parameters)
    {
        builder.Reset(uri);
        scanner.Reset(data);
        matcher.Reset();
    }

    template<typename BuilderType>
    auto ParserBase<BuilderType>::GetResult() const -> result_type
    {
        return builder.GetResult();
    }
}

#endif
