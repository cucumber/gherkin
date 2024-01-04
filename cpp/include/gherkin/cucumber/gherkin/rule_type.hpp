// This file is generated. Do not edit! Edit gherkin-cpp-rule-type.razor instead.
#pragma once

#include <ostream>
#include <string_view>

namespace cucumber::gherkin {

enum class rule_type
{
    none = 0,
    e_o_f,
    empty,
    comment,
    tag_line,
    feature_line,
    rule_line,
    background_line,
    scenario_line,
    examples_line,
    step_line,
    doc_string_separator,
    table_row,
    language,
    other,
    gherkin_document,
    feature,
    feature_header,
    rule,
    rule_header,
    background,
    scenario_definition,
    scenario,
    examples_definition,
    examples,
    examples_table,
    step,
    step_arg,
    data_table,
    doc_string,
    tags,
    description_helper,
    description,
    count
};

std::string_view
to_string(rule_type r);

inline
std::ostream&
operator<<(std::ostream& os, rule_type r)
{
    os << to_string(r);

    return os;
}

}
