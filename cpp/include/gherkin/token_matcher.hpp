#pragma once

#include <string>

#include <gherkin/dialect.hpp>
#include <gherkin/token.hpp>
#include <gherkin/types.hpp>

namespace gherkin {

using keyword_types_map = std::unordered_map<std::string_view, string_views>;

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
        std::string_view token_type,
        string_views keywords
    );

    struct token_info
    {
        std::string text;
        std::string keyword;
        std::string keyword_type;
        std::size_t indent;
        gherkin::items items;
    };

    void set_token_matched(
        token& token,
        std::string_view matched_type,
        const token_info& ti = {}
    );

    const string_views& keywords(std::string_view kw) const;

    std::string_view keyword_type(std::string_view keyword) const;

    void change_dialect(const std::string& dialect_name);

    std::string unescape_docstring(const std::string& text) const;

    std::string dialect_name_;
    keyword_types_map keyword_types_;
    std::string active_doc_string_separator_;
    std::size_t indent_to_remove_;
};

}
