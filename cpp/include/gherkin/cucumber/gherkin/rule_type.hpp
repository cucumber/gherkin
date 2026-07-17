// This File is generated. Do not edit! Edit gherkin-cpp-rule-type.razor instead.
#ifndef CUCUMBER_GHERKIN_RULE_TYPE_HPP
#define CUCUMBER_GHERKIN_RULE_TYPE_HPP

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cucumber::gherkin
{

    enum class RuleType : std::uint8_t
    {
        NONE = 0,
        E_O_F,
        EMPTY,
        COMMENT,
        TAG_LINE,
        FEATURE_LINE,
        RULE_LINE,
        BACKGROUND_LINE,
        SCENARIO_LINE,
        EXAMPLES_LINE,
        STEP_LINE,
        DOC_STRING_SEPARATOR,
        TABLE_ROW,
        LANGUAGE,
        OTHER,
        GHERKIN_DOCUMENT,
        FEATURE,
        FEATURE_HEADER,
        RULE,
        RULE_HEADER,
        BACKGROUND,
        SCENARIO_DEFINITION,
        SCENARIO,
        EXAMPLES_DEFINITION,
        EXAMPLES,
        EXAMPLES_TABLE,
        STEP,
        STEP_ARG,
        DATA_TABLE_AND_MAYBE_DOC_STRING,
        DOC_STRING_AND_MAYBE_DATA_TABLE,
        DATA_TABLE,
        DOC_STRING,
        TAGS,
        DESCRIPTION_HELPER,
        DESCRIPTION,
        COUNT
    };

    std::string_view to_string(RuleType type);

    inline std::ostream& operator<<(std::ostream& ostream, RuleType type)
    {
        ostream << to_string(type);

        return ostream;
    }

}

#endif
