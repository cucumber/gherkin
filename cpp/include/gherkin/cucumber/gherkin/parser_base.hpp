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
        using ResultType = typename BuilderType::ResultType;
        using ContextType = ParserContext<BuilderType>;

        ParserBase() = default;
        explicit ParserBase(IdGeneratorPtr idp);

        virtual ~ParserBase() = default;
        ParserBase(const ParserBase&) = delete;
        ParserBase& operator=(const ParserBase&) = delete;
        ParserBase(ParserBase&&) = delete;
        ParserBase& operator=(ParserBase&&) = delete;

        ResultType Parse(std::string_view uri, std::string_view data);

    protected:
        void Reset(std::string_view uri, std::string_view data);

        [[nodiscard]] ResultType GetResult() const;

        virtual void parse(ContextType& context) = 0; // NOLINT(readability-identifier-naming)

        BuilderType builder;  // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
        TokenScanner scanner; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
        TokenMatcher matcher; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
    };

    template<typename BuilderType>
    ParserBase<BuilderType>::ParserBase(IdGeneratorPtr idp)
        : builder{ std::move(idp) }
    {}

    template<typename BuilderType>
    auto ParserBase<BuilderType>::Parse(std::string_view uri, std::string_view data) -> ResultType
    {
        Reset(uri, data);

        ContextType context{ builder, scanner, matcher };

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
    auto ParserBase<BuilderType>::GetResult() const -> ResultType
    {
        return builder.GetResult();
    }
}

#endif
