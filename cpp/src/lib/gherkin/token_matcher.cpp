
#include <gherkin/token_matcher.hpp>
#include <gherkin/dialect.hpp>
#include <gherkin/utils.hpp>
#include <gherkin/regex.hpp>

namespace gherkin {

static const std::regex language_re{
    "\\s*#\\s*language\\s*:\\s*([a-zA-Z\\-_]+)\\s*"
};

token_matcher::token_matcher(const token_matcher_info& tmi)
: tmi_(tmi)
{
    change_dialect(tmi.dialect);
}

token_matcher::~token_matcher()
{}

void
token_matcher::reset()
{}

bool
token_matcher::match_feature_line(token& token)
{ return match_title_line(token, "FeatureLine", keywords("feature")); }

bool
token_matcher::match_rule_line(token& token)
{ return match_title_line(token, "RuleLine", keywords("rule")); }

bool
token_matcher::match_scenario_line(token& token)
{
    return
        match_title_line(token, "ScenarioLine", keywords("scenario"))
        ||
        match_title_line(token, "ScenarioLine", keywords("scenarioOutline"))
        ;
}

bool
token_matcher::match_background_line(token& token)
{ return match_title_line(token, "BackgroundLine", keywords("background")); }

bool
token_matcher::match_examples_line(token& token)
{ return match_title_line(token, "ExamplesLine", keywords("examples")); }

bool
token_matcher::match_table_row(token& token)
{
    if (!token.line.startswith("|")) {
        return false;
    }

    set_token_matched(
        token, "TableRow", { .items = token.line.table_cells() }
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

    set_token_matched(token, "Language", { .text = dialect_name });
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
        token, "TagLine", {
            .items = std::move(token.line.tags())
        }
    );

    return true;
}

bool
token_matcher::match_title_line(
    token& token,
    std::string_view text,
    string_views keywords
)
{ return true; }

bool
token_matcher::match_e_o_f(token& token)
{ return true; }

bool
token_matcher::match_empty(token& token)
{
    if (!token.line.is_empty()) {
        return false;
    }

    set_token_matched(token, "Empty", { .indent = 0 } );

    return true;
}

bool
token_matcher::match_comment(token& token)
{
    if (!token.line.startswith("#")) {
        return false;
    }

    set_token_matched(
        token, "Comment", {
            .text = std::string(token.line.line_text())
        }
    );

    return true;
}

bool
token_matcher::match_other(token& token)
{ return true; }

bool
token_matcher::match_step_line(token& token)
{
    string_views kws = { "given", "when", "then", "and", "but" };
    auto keywords = gherkin::keywords(dialect_name_, kws);

    for (const auto& keyword : keywords) {
        if (!token.line.startswith(keyword)) {
            continue;
        }

        auto title = token.line.get_rest_trimmed(keyword.size());

        set_token_matched(
            token, "StepLine", {
                .text = std::string(title),
                .keyword = std::string(keyword),
                .keyword_type = std::string(keyword_type(keyword))
            }
        );

        return true;
    }

    return false;
}

bool
token_matcher::match_doc_string_separator(token& token)
{ return true; }

void
token_matcher::set_token_matched(
    token& token,
    std::string_view text,
    const token_info& ti
)
{
    token.matched_type = ti.keyword_type;
    token.matched_text.assign(rstrip(ti.text, "\r\n"));
    token.matched_keyword = ti.keyword;

    if (ti.indent) {
        token.matched_indent = ti.indent;
    } else {
        token.matched_indent = token.line.indent();
    }
    token.matched_items = std::move(ti.items);
    token.matched_gherkin_dialect = dialect_name_;
}

const string_views&
token_matcher::keywords(std::string_view kw) const
{ return gherkin::keywords(tmi_.dialect, kw); }

std::string_view
token_matcher::keyword_type(std::string_view keyword) const
{
    auto it = keyword_types_.find(keyword);

    if (it != keyword_types_.end()) {
        const auto& kws = it->second;

        if (!kws.empty()) {
            return kws[0];
        }
    }

    return "Unknown";
}

void
token_matcher::change_dialect(const std::string& dialect_name)
{
    dialect_name_ = dialect_name;

    auto d = get_dialect(dialect_name_);

    keyword_types_.clear();

    for (const auto& keyword : d.given_keywords) {
        keyword_types_[keyword].push_back("Context");
    }

    for (const auto& keyword : d.when_keywords) {
        keyword_types_[keyword].push_back("Action");
    }

    for (const auto& keyword : d.then_keywords) {
        keyword_types_[keyword].push_back("Outcome");
    }

    for (const auto& keyword : d.and_keywords) {
        keyword_types_[keyword].push_back("Conjunction");
    }

    for (const auto& keyword : d.but_keywords) {
        keyword_types_[keyword].push_back("Conjunction");
    }
}

}
