#include "cucumber/gherkin/token_formatter_builder.hpp"
#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/join_utils.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/types.hpp"
#include <sstream>
#include <string>
#include <string_view>

namespace cucumber::gherkin
{

    token_formatter_builder::token_formatter_builder(id_generator_ptr idp)
        : idp_(idp)
    {}

    token_formatter_builder::~token_formatter_builder()
    {}

    void token_formatter_builder::reset(std::string_view uri)
    {
        formatted_tokens_.clear();
    }

    void token_formatter_builder::start_rule(rule_type rule_type)
    {}

    void token_formatter_builder::end_rule(rule_type rule_type)
    {}

    void token_formatter_builder::build(const token& token)
    {
        formatted_tokens_.emplace_back(format_token(token));
    }

    strings token_formatter_builder::get_result() const
    {
        return formatted_tokens_;
    }

    std::string token_formatter_builder::format_token(const token& token)
    {
        if (token.is_eof())
        {
            return "EOF";
        }

        std::ostringstream stream;

        stream << "(" << token.location.line << ":" << token.location.column.value_or(0) << ")" << token.matched_type << ":";

        if (token.matched_keyword)
        {
            stream << "(";

            if (token.matched_keyword_type)
            {
                stream << *token.matched_keyword_type;
            }

            stream << ")" << token.matched_keyword.value();
        }

        stream << "/" << token.matched_text << "/";

        if (!token.matched_items.empty())
        {
            strings items;

            for (const auto& matched_item : token.matched_items)
            {
                items.emplace_back(std::to_string(matched_item.column) + ":" + matched_item.text);
            }

            stream << join(",", items);
        }

        return stream.str();
    }

}
