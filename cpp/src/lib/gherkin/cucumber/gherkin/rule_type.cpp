#include "cucumber/gherkin/rule_type.hpp"
#include <string_view>
#include <unordered_map>

namespace cucumber::gherkin
{

    std::string_view to_string(RuleType type)
    {
        static const std::unordered_map<RuleType, std::string_view> rmap = { { RuleType::none, "None" }, { RuleType::e_o_f, "EOF" }, { RuleType::empty, "Empty" },
            { RuleType::comment, "Comment" }, { RuleType::tag_line, "TagLine" }, { RuleType::feature_line, "FeatureLine" }, { RuleType::rule_line, "RuleLine" },
            { RuleType::background_line, "BackgroundLine" }, { RuleType::scenario_line, "ScenarioLine" }, { RuleType::examples_line, "ExamplesLine" }, { RuleType::step_line, "StepLine" },
            { RuleType::doc_string_separator, "DocStringSeparator" }, { RuleType::table_row, "TableRow" }, { RuleType::language, "Language" }, { RuleType::other, "Other" },
            { RuleType::gherkin_document, "GherkinDocument" }, { RuleType::feature, "Feature" }, { RuleType::feature_header, "FeatureHeader" }, { RuleType::rule, "Rule" },
            { RuleType::rule_header, "RuleHeader" }, { RuleType::background, "Background" }, { RuleType::scenario_definition, "ScenarioDefinition" }, { RuleType::scenario, "Scenario" },
            { RuleType::examples_definition, "ExamplesDefinition" }, { RuleType::examples, "Examples" }, { RuleType::examples_table, "ExamplesTable" }, { RuleType::step, "Step" },
            { RuleType::step_arg, "StepArg" }, { RuleType::data_table, "DataTable" }, { RuleType::doc_string, "DocString" }, { RuleType::tags, "Tags" },
            { RuleType::description_helper, "DescriptionHelper" }, { RuleType::description, "Description" } };

        return rmap.at(type);
    }

}
