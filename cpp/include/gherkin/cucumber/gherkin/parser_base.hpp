#ifndef CUCUMBER_GHERKIN_PARSER_BASE_HPP
#define CUCUMBER_GHERKIN_PARSER_BASE_HPP

#include "cucumber/gherkin/ast_builder.hpp"
#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/parser_context.hpp"
#include "cucumber/gherkin/token_matcher.hpp"
#include "cucumber/gherkin/token_scanner.hpp"
#include "cucumber/messages/Source.hpp"
#include <string_view>

namespace cucumber::gherkin
{

    namespace cms = cucumber::messages;

    template<typename Builder = AstBuilder, typename Scanner = TokenScanner, typename Matcher = TokenMatcher>
    class ParserBase
    {
    public:
        using result_type = typename Builder::result_type;
        using context_type = ParserContext<Builder, Scanner, Matcher>;

        ParserBase() = default;

        ParserBase(id_generator_ptr idp)
            : builder(idp)
        {}

        virtual ~ParserBase() = default;
        ParserBase(const ParserBase&) = delete;
        ParserBase& operator=(const ParserBase&) = delete;
        ParserBase(ParserBase&&) = delete;
        ParserBase& operator=(ParserBase&&) = delete;

        result_type Parse(std::string_view uri, std::string_view data)
        {
            Reset(uri, data);

            context_type context{ builder, scanner, matcher };

            parse(context);

            return GetResult();
        }

    protected:
        void Reset(std::string_view uri, std::string_view data) // NOLINT(bugprone-easily-swappable-parameters)
        {
            builder.Reset(uri);
            scanner.Reset(data);
            matcher.Reset();
        }

        result_type GetResult() const
        {
            return builder.GetResult();
        }

        virtual void parse(context_type& context) = 0;

        Builder builder; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
        Scanner scanner; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
        Matcher matcher; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
    };

}

#endif
