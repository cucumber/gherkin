#include <gherkin/token_matcher.hpp>
#include <gherkin/dialect.hpp>

namespace gherkin {

token_matcher::token_matcher(const token_matcher_info& tmi)
: tmi_(tmi)
{}

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
    return true;
}

bool
token_matcher::match_language(token& token)
{ return true; }

bool
token_matcher::match_tag_line(token& token)
{ return true; }

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
{ return true; }

bool
token_matcher::match_comment(token& token)
{ return true; }

bool
token_matcher::match_other(token& token)
{ return true; }

bool
token_matcher::match_step_line(token& token)
{ return true; }

bool
token_matcher::match_doc_string_separator(token& token)
{ return true; }

const string_views&
token_matcher::keywords(std::string_view kw) const
{ return gherkin::keywords(tmi_.dialect, kw); }

}
