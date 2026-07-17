#include "cucumber/gherkin/rule_type.hpp"
#include <string_view>
#include <unordered_map>

namespace cucumber::gherkin
{

    std::string_view to_string(RuleType type)
    {
        static const std::unordered_map<RuleType, std::string_view> rmap = { { RuleType::none, "None" }, { RuleType::eOF, "EOF" }, { RuleType::empty, "Empty" }, { RuleType::comment, "Comment" },
            { RuleType::tagLine, "TagLine" }, { RuleType::featureLine, "FeatureLine" }, { RuleType::ruleLine, "RuleLine" }, { RuleType::backgroundLine, "BackgroundLine" },
            { RuleType::scenarioLine, "ScenarioLine" }, { RuleType::examplesLine, "ExamplesLine" }, { RuleType::stepLine, "StepLine" }, { RuleType::docStringSeparator, "DocStringSeparator" },
            { RuleType::tableRow, "TableRow" }, { RuleType::language, "Language" }, { RuleType::other, "Other" }, { RuleType::gherkinDocument, "GherkinDocument" }, { RuleType::feature, "Feature" },
            { RuleType::featureHeader, "FeatureHeader" }, { RuleType::rule, "Rule" }, { RuleType::ruleHeader, "RuleHeader" }, { RuleType::background, "Background" },
            { RuleType::scenarioDefinition, "ScenarioDefinition" }, { RuleType::scenario, "Scenario" }, { RuleType::examplesDefinition, "ExamplesDefinition" }, { RuleType::examples, "Examples" },
            { RuleType::examplesTable, "ExamplesTable" }, { RuleType::step, "Step" }, { RuleType::stepArg, "StepArg" }, { RuleType::dataTable, "DataTable" }, { RuleType::docString, "DocString" },
            { RuleType::tags, "Tags" }, { RuleType::descriptionHelper, "DescriptionHelper" }, { RuleType::description, "Description" } };

        return rmap.at(type);
    }

}
