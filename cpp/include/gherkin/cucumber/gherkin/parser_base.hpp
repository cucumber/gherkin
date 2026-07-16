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

        ParserBase()
        {}

        ParserBase(id_generator_ptr idp)
            : builder_(idp)
        {}

        virtual ~ParserBase()
        {}

        result_type parse(std::string_view uri, std::string_view data)
        {
            reset(uri, data);

            context_type context{ builder_, scanner_, matcher_ };

            parse(context);

            return get_result();
        }

    protected:
        void reset(std::string_view uri, std::string_view data)
        {
            builder_.reset(uri);
            scanner_.reset(data);
            matcher_.reset();
        }

        result_type get_result() const
        {
            return builder_.get_result();
        }

        virtual void parse(context_type& context) = 0;

        Builder builder_;
        Scanner scanner_;
        Matcher matcher_;
    };

}

#endif
