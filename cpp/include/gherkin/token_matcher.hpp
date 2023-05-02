#pragma once

namespace gherkin {

struct token_matcher_info
{
    std::string dialect = "en";
};

class token_matcher
{
public:
    token_matcher(const token_matcher_info& tmi = {});
    virtual ~token_matcher();

    void reset();

    bool match_feature_line(token& token);
    bool match_rule_line(token& token);
    bool match_scenario_line(token& token);
    bool match_background_line(token& token);
    bool match_examples_line(token& token);
    bool match_language(token& token);
    bool match_tag_line(token& token);
    bool match_title_line(token& token);
    bool match_e_o_f(token& token);
    bool match_empty(token& token);
    bool match_comment(token& token);
    bool match_other(token& token);
    bool match_step_line(token& token);
    bool match_doc_string_separator(token& token);
    bool match_table_row(token& token);

private:
    token_matcher_info tmi_;
};

}
