
#include <cucumber/gherkin/token_matcher.hpp>
#include <cucumber/gherkin/keywords.hpp>
#include <cucumber/gherkin/utils.hpp>
#include <cucumber/gherkin/regex.hpp>
#include <cucumber/gherkin/exceptions.hpp>

namespace cucumber::gherkin {

static const std::regex language_re{
    "^\\s*#\\s*language\\s*:\\s*([a-zA-Z\\-_]+)\\s*$"
};

token_matcher::token_matcher(const std::string& dialect_name)
{
    change_dialect(dialect_name);
}

token_matcher::~token_matcher()
{}

void
token_matcher::reset()
{
    indent_to_remove_ = 0;
    active_doc_string_separator_.clear();
}

bool
token_matcher::match_feature_line(token& token)
{
    return
        match_title_line(
            token,
            rule_type::feature_line,
            keywords("feature")
        );
}

bool
token_matcher::match_rule_line(token& token)
{ return match_title_line(token, rule_type::rule_line, keywords("rule")); }

bool
token_matcher::match_scenario_line(token& token)
{
    auto rt = rule_type::scenario_line;

    return
        match_title_line(token, rt, keywords("scenario"))
        ||
        match_title_line(token, rt, keywords("scenarioOutline"))
        ;
}

bool
token_matcher::match_background_line(token& token)
{
    return
        match_title_line(
            token,
            rule_type::background_line,
            keywords("background")
        );
}

bool
token_matcher::match_examples_line(token& token)
{
    return
        match_title_line(
            token,
            rule_type::examples_line,
            keywords("examples")
        );
}

bool
token_matcher::match_table_row(token& token)
{
    if (!token.line.startswith("|")) {
        return false;
    }

    set_token_matched(
        token, rule_type::table_row, { .items = token.line.table_cells() }
    );

    return true;
}

bool
token_matcher::match_language(token& token)
{
    std::string dialect_name;

    if (!full_match(token.line.line_text(), language_re, dialect_name)) {
        return false;
    }

    set_token_matched(token, rule_type::language, { .text = dialect_name });
    change_dialect(dialect_name);

    return true;
}

bool
token_matcher::match_tag_line(token& token)
{
    if (!token.line.startswith("@")) {
        return false;
    }

    set_token_matched(
        token, rule_type::tag_line, {
            .items = std::move(token.line.tags())
        }
    );

    return true;
}

bool
token_matcher::match_title_line(
    token& token,
    rule_type token_type,
    string_views keywords
)
{
    for (const auto& keyword : keywords) {
        std::string k(keyword);

        if (!token.line.startswith_title_keyword(k)) {
            continue;
        }

        set_token_matched(
            token, token_type, {
                .text = token.line.get_keyword_trimmed(k),
                .keyword = k
            }
        );

        return true;
    }

    return false;
}

bool
token_matcher::match_e_o_f(token& token)
{
    if (!token.eof) {
        return false;
    }

    set_token_matched(token, rule_type::e_o_f);

    return true;
}

bool
token_matcher::match_empty(token& token)
{
    if (!token.line.is_empty()) {
        return false;
    }

    set_token_matched(token, rule_type::empty, { .indent = 0 } );

    return true;
}

bool
token_matcher::match_comment(token& token)
{
    if (!token.line.startswith("#")) {
        return false;
    }

    auto comment_text = std::string(token.line.get_line_text(0));

    subst(comment_text, "[\\r\\n]+$");

    set_token_matched(
        token, rule_type::comment, {
            .text = comment_text,
            .indent = 0
        }
    );

    return true;
}

bool
token_matcher::match_other(token& token)
{
    std::string text = std::string(token.line.get_line_text(indent_to_remove_));

    set_token_matched(
        token, rule_type::other, {
            .text = unescape_docstring(text),
            .indent = 0
        }
    );

    return true;
}

bool
token_matcher::match_step_line(token& token)
{
    string_views kws = { "given", "when", "then", "and", "but" };
    auto keywords = cucumber::gherkin::keywords(dialect_name_, kws);

    for (const auto& keyword : keywords) {
        if (!token.line.startswith(keyword)) {
            continue;
        }

        auto title = token.line.get_rest_trimmed(keyword.size());

        set_token_matched(
            token, rule_type::step_line, {
                .text = title,
                .keyword = std::string(keyword),
                .keyword_type = keyword_type(keyword)
            }
        );

        return true;
    }

    return false;
}

bool
token_matcher::match_doc_string_separator(token& token)
{
    if (active_doc_string_separator_.empty()) {
        return
            match_doc_string_separator_(token, "\"\"\"", true)
            ||
            match_doc_string_separator_(token, "```", true);
    }

    return
        match_doc_string_separator_(
            token, active_doc_string_separator_, false
        );
}

bool
token_matcher::match_doc_string_separator_(
    token& token,
    std::string_view separator,
    bool is_open
)
{
    if (!token.line.startswith(separator)) {
        return false;
    }

    std::string content_type;
    std::string tseparator = std::string(separator);

    if (is_open) {
        content_type = token.line.get_rest_trimmed(separator.size());
        active_doc_string_separator_ = tseparator;
        indent_to_remove_ = token.line.indent();
    } else {
        active_doc_string_separator_.clear();
        indent_to_remove_ = 0;
    }

    set_token_matched(
        token, rule_type::doc_string_separator, {
            .text = content_type,
            .keyword = tseparator
        }
    );

    return true;
}

void
token_matcher::set_token_matched(
    token& token,
    rule_type matched_type,
    const token_info& ti
)
{
    using namespace std::literals;

    token.matched_type = matched_type;

    if (ti.text) {
        token.matched_text.assign(rstrip(*ti.text, re_pattern::crlf));
    }

    if (ti.keyword) {
        token.matched_keyword = *ti.keyword;
    }

    if (ti.keyword_type) {
        token.matched_keyword_type = *ti.keyword_type;
    }

    if (ti.indent) {
        token.matched_indent = *ti.indent;
    } else {
        token.matched_indent = token.line.indent();
    }

    token.matched_items = std::move(ti.items);
    token.location.column = token.matched_indent + 1;
    token.matched_gherkin_dialect = dialect_name_;
}

const string_views&
token_matcher::keywords(std::string_view kw) const
{ return cucumber::gherkin::keywords(dialect_name_, kw); }

cucumber::messages::step_keyword_type
token_matcher::keyword_type(std::string_view keyword) const
{
    auto it = keyword_types_.find(keyword);

    if (it != keyword_types_.end()) {
        const auto& kws = it->second;

        if (kws.size() == 1) {
            return kws[0];
        }
    }

    return cucumber::messages::step_keyword_type::UNKNOWN;
}

void
token_matcher::change_dialect(
    const std::string& dialect_name,
    const cms::location& location
)
{
    if (all_keywords().find(dialect_name) == all_keywords().end()) {
        throw no_such_language_error(dialect_name, location);
    }

    dialect_name_ = dialect_name;

    auto d = get_dialect(dialect_name_);

    keyword_types_.clear();

    for (const auto& keyword : d.given_keywords) {
        keyword_types_[keyword].push_back(
            cucumber::messages::step_keyword_type::CONTEXT
        );
    }

    for (const auto& keyword : d.when_keywords) {
        keyword_types_[keyword].push_back(
            cucumber::messages::step_keyword_type::ACTION
        );
    }

    for (const auto& keyword : d.then_keywords) {
        keyword_types_[keyword].push_back(
            cucumber::messages::step_keyword_type::OUTCOME
        );
    }

    for (const auto& keyword : d.and_keywords) {
        keyword_types_[keyword].push_back(
            cucumber::messages::step_keyword_type::CONJUNCTION
        );
    }

    for (const auto& keyword : d.but_keywords) {
        keyword_types_[keyword].push_back(
            cucumber::messages::step_keyword_type::CONJUNCTION
        );
    }
}

std::string
token_matcher::unescape_docstring(const std::string& text) const
{
    using namespace std::literals;

    std::string u;

    if (active_doc_string_separator_ == "\"\"\"") {
        u = subst(text, "\\\\\"\\\\\"\\\\\"", "\"\"\"");
    } else if (active_doc_string_separator_ == "```") {
        u = subst(text, "\\\\`\\\\`\\\\`", "```");
    } else {
        u = text;
    }

    return u;
}

}
