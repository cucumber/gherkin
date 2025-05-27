#pragma once

#include <string>
#include <optional>

#include <cucumber/messages/step_keyword_type.hpp>

#include <cucumber/gherkin/dialect.hpp>
#include <cucumber/gherkin/token.hpp>
#include <cucumber/gherkin/types.hpp>
#include <cucumber/gherkin/rule_type.hpp>

namespace cucumber::gherkin {

using keyword_types = std::vector<cucumber::messages::step_keyword_type>;
using keyword_types_map = std::unordered_map<std::string_view, keyword_types>;

class token_matcher
{
public:
    token_matcher(const std::string& dialect_name = "en");
    virtual ~token_matcher();

    void reset();

    bool match_feature_line(token& token);
    bool match_rule_line(token& token);
    bool match_scenario_line(token& token);
    bool match_background_line(token& token);
    bool match_examples_line(token& token);
    bool match_language(token& token);
    bool match_tag_line(token& token);
    bool match_e_o_f(token& token);
    bool match_empty(token& token);
    bool match_comment(token& token);
    bool match_other(token& token);
    bool match_step_line(token& token);
    bool match_doc_string_separator(token& token);
    bool match_table_row(token& token);

private:
    bool match_doc_string_separator_(
        token& token,
        std::string_view separator,
        bool is_open
    );

    bool match_title_line(
        token& token,
        rule_type token_type,
        string_views keywords
    );

    struct token_info
    {
        std::optional<std::string> text;
        std::optional<std::string> keyword;
        std::optional<cms::step_keyword_type> keyword_type;
        std::optional<std::size_t> indent;
        cucumber::gherkin::items items;
    };

    void set_token_matched(
        token& token,
        rule_type matched_type,
        const token_info& ti = {}
    );

    const string_views& keywords(std::string_view kw) const;

    cucumber::messages::step_keyword_type
    keyword_type(std::string_view keyword) const;

    void change_dialect(
        const std::string& dialect_name,
        const cms::location& location = { 1, 1 }
    );

    std::string unescape_docstring(const std::string& text) const;

    std::string dialect_name_;
    keyword_types_map keyword_types_;
    std::string active_doc_string_separator_;
    std::size_t indent_to_remove_;
};

}
