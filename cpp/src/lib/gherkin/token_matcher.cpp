#include <gherkin/token_matcher.hpp>

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
{ return true; }

bool
token_matcher::match_rule_line(token& token)
{ return true; }

bool
token_matcher::match_scenario_line(token& token)
{ return true; }

bool
token_matcher::match_background_line(token& token)
{ return true; }

bool
token_matcher::match_examples_line(token& token)
{ return true; }

bool
token_matcher::match_language(token& token)
{ return true; }

bool
token_matcher::match_tag_line(token& token)
{ return true; }

bool
token_matcher::match_title_line(token& token)
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

bool
token_matcher::match_table_row(token& token)
{ return true; }

    }
