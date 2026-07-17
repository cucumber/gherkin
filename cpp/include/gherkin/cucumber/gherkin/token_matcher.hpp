#ifndef CUCUMBER_GHERKIN_TOKEN_MATCHER_HPP
#define CUCUMBER_GHERKIN_TOKEN_MATCHER_HPP

#include "cucumber/gherkin/items.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/types.hpp"
#include "cucumber/messages/StepKeywordType.hpp"
#include <cstddef>
#include <cucumber/messages/Location.hpp>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace cucumber::gherkin
{

    using keyword_types = std::vector<cucumber::messages::StepKeywordType>;
    using keyword_types_map = std::unordered_map<std::string_view, keyword_types>;

    class TokenMatcher
    {
    public:
        TokenMatcher(const std::string& dialect_name = "en");
        virtual ~TokenMatcher();

        void reset();

        bool match_feature_line(Token& token);
        bool match_rule_line(Token& token);
        bool match_scenario_line(Token& token);
        bool match_background_line(Token& token);
        bool match_examples_line(Token& token);
        bool match_language(Token& token);
        bool match_tag_line(Token& token);
        bool match_e_o_f(Token& token);
        bool match_empty(Token& token);
        bool match_comment(Token& token);
        bool match_other(Token& token);
        bool match_step_line(Token& token);
        bool match_doc_string_separator(Token& token);
        bool match_table_row(Token& token);

    private:
        bool match_doc_string_separator_(Token& token, std::string_view separator, bool is_open);

        bool match_title_line(Token& token, RuleType token_type, string_views keywords);

        struct TokenInfo
        {
            std::optional<std::string> text;
            std::optional<std::string> keyword;
            std::optional<cms::StepKeywordType> keyword_type;
            std::optional<std::size_t> indent;
            cucumber::gherkin::items items;
        };

        void set_token_matched(Token& token, RuleType matched_type, const TokenInfo& info = {});

        const string_views& keywords(std::string_view keyword) const;

        cucumber::messages::StepKeywordType keyword_type(std::string_view keyword) const;

        void change_dialect(const std::string& dialect_name, const cms::Location& location = { 1, 1 });

        std::string unescape_docstring(const std::string& text) const;

        std::string dialect_name_;
        keyword_types_map keyword_types_;
        std::string active_doc_string_separator_;
        std::size_t indent_to_remove_;
    };

}

#endif
