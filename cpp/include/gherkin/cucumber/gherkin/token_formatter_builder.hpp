#ifndef CUCUMBER_GHERKIN_TOKEN_FORMATTER_BUILDER_HPP
#define CUCUMBER_GHERKIN_TOKEN_FORMATTER_BUILDER_HPP

#include "cucumber/gherkin/ast_node.hpp"
#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/msg_types.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/messages/All.hpp"

namespace cucumber::gherkin
{

    namespace cms = cucumber::messages;

    class token_formatter_builder
    {
    public:
        using result_type = strings;

        token_formatter_builder(id_generator_ptr idp = {});
        virtual ~token_formatter_builder();

        void reset(std::string_view uri);

        void start_rule(rule_type rule_type);
        void end_rule(rule_type rule_type);
        void build(const token& token);

        strings get_result() const;

    private:
        std::string format_token(const token& token);

        id_generator_ptr idp_;
        strings formatted_tokens_;
    };

}

#endif
