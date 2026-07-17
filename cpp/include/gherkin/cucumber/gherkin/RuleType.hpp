#ifndef CUCUMBER_GHERKIN_RULE_TYPE_HPP
#define CUCUMBER_GHERKIN_RULE_TYPE_HPP

#include <cstdint>
#include <ostream>
#include <string_view>

// This File is generated. Do not edit! Edit gherkin-cpp-rule-type.razor instead.

namespace cucumber::gherkin
{

    enum class RuleType : std::uint8_t
    {
        none = 0,
        eOF,
        empty,
        comment,
        tagLine,
        featureLine,
        ruleLine,
        backgroundLine,
        scenarioLine,
        examplesLine,
        stepLine,
        docStringSeparator,
        tableRow,
        language,
        other,
        gherkinDocument,
        feature,
        featureHeader,
        rule,
        ruleHeader,
        background,
        scenarioDefinition,
        scenario,
        examplesDefinition,
        examples,
        examplesTable,
        step,
        stepArg,
        dataTableAndMaybeDocString,
        docStringAndMaybeDataTable,
        dataTable,
        docString,
        tags,
        descriptionHelper,
        description,
        count
    };

    [[nodiscard]] std::string_view to_string(RuleType type);

    inline std::ostream& operator<<(std::ostream& ostream, RuleType type)
    {
        ostream << to_string(type);

        return ostream;
    }

}

#endif
