#include "cucumber/gherkin/rule_type.hpp"
#include <string_view>
#include <unordered_map>

namespace cucumber::gherkin
{

    std::string_view to_string(RuleType type)
    {
        static const std::unordered_map<RuleType, std::string_view> rmap = { { RuleType::NONE, "None" }, { RuleType::E_O_F, "EOF" }, { RuleType::EMPTY, "Empty" }, { RuleType::COMMENT, "Comment" },
            { RuleType::TAG_LINE, "TagLine" }, { RuleType::FEATURE_LINE, "FeatureLine" }, { RuleType::RULE_LINE, "RuleLine" }, { RuleType::BACKGROUND_LINE, "BackgroundLine" },
            { RuleType::SCENARIO_LINE, "ScenarioLine" }, { RuleType::EXAMPLES_LINE, "ExamplesLine" }, { RuleType::STEP_LINE, "StepLine" }, { RuleType::DOC_STRING_SEPARATOR, "DocStringSeparator" },
            { RuleType::TABLE_ROW, "TableRow" }, { RuleType::LANGUAGE, "Language" }, { RuleType::OTHER, "Other" }, { RuleType::GHERKIN_DOCUMENT, "GherkinDocument" }, { RuleType::FEATURE, "Feature" },
            { RuleType::FEATURE_HEADER, "FeatureHeader" }, { RuleType::RULE, "Rule" }, { RuleType::RULE_HEADER, "RuleHeader" }, { RuleType::BACKGROUND, "Background" },
            { RuleType::SCENARIO_DEFINITION, "ScenarioDefinition" }, { RuleType::SCENARIO, "Scenario" }, { RuleType::EXAMPLES_DEFINITION, "ExamplesDefinition" }, { RuleType::EXAMPLES, "Examples" },
            { RuleType::EXAMPLES_TABLE, "ExamplesTable" }, { RuleType::STEP, "Step" }, { RuleType::STEP_ARG, "StepArg" }, { RuleType::DATA_TABLE, "DataTable" }, { RuleType::DOC_STRING, "DocString" },
            { RuleType::TAGS, "Tags" }, { RuleType::DESCRIPTION_HELPER, "DescriptionHelper" }, { RuleType::DESCRIPTION, "Description" } };

        return rmap.at(type);
    }

}
