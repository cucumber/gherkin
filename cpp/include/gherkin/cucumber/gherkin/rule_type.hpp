// This File is generated. Do not edit! Edit gherkin-cpp-rule-type.razor instead.
#ifndef CUCUMBER_GHERKIN_RULE_TYPE_HPP
#define CUCUMBER_GHERKIN_RULE_TYPE_HPP

#include <ostream>
#include <string_view>

namespace cucumber::gherkin
{

    enum class RuleType
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
        data_table_and_maybe_doc_string,
        doc_string_and_maybe_data_table,
        data_table,
        doc_string,
        tags,
        description_helper,
        description,
        count
    };

    std::string_view to_string(RuleType type);

    inline std::ostream& operator<<(std::ostream& ostream, RuleType type)
    {
        ostream << to_string(type);

        return ostream;
    }

}

#endif
