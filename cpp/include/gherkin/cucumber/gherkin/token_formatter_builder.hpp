#ifndef CUCUMBER_GHERKIN_TOKEN_FORMATTER_BUILDER_HPP
#define CUCUMBER_GHERKIN_TOKEN_FORMATTER_BUILDER_HPP

#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/types.hpp"
#include <string>
#include <string_view>

namespace cucumber::gherkin
{

    namespace cms = cucumber::messages;

    class TokenFormatterBuilder
    {
    public:
        using result_type = strings;

        TokenFormatterBuilder(id_generator_ptr idp = {});
        virtual ~TokenFormatterBuilder();

        void reset(std::string_view uri);

        void start_rule(RuleType RuleType);
        void end_rule(RuleType RuleType);
        void build(const Token& token);

        strings get_result() const;

    private:
        std::string format_token(const Token& token);

        id_generator_ptr idp_;
        strings formatted_tokens_;
    };

}

#endif
