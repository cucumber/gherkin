#include <unordered_map>

#include <cucumber/gherkin/rule_type.hpp>

namespace cucumber::gherkin {

std::string_view
to_string(rule_type r)
{
    static const std::unordered_map<rule_type, std::string_view> rmap = {
        { rule_type::none, "None" },
        { rule_type::e_o_f, "EOF" },
        { rule_type::empty, "Empty" },
        { rule_type::comment, "Comment" },
        { rule_type::tag_line, "TagLine" },
        { rule_type::feature_line, "FeatureLine" },
        { rule_type::rule_line, "RuleLine" },
        { rule_type::background_line, "BackgroundLine" },
        { rule_type::scenario_line, "ScenarioLine" },
        { rule_type::examples_line, "ExamplesLine" },
        { rule_type::step_line, "StepLine" },
        { rule_type::doc_string_separator, "DocStringSeparator" },
        { rule_type::table_row, "TableRow" },
        { rule_type::language, "Language" },
        { rule_type::other, "Other" },
        { rule_type::gherkin_document, "GherkinDocument" },
        { rule_type::feature, "Feature" },
        { rule_type::feature_header, "FeatureHeader" },
        { rule_type::rule, "Rule" },
        { rule_type::rule_header, "RuleHeader" },
        { rule_type::background, "Background" },
        { rule_type::scenario_definition, "ScenarioDefinition" },
        { rule_type::scenario, "Scenario" },
        { rule_type::examples_definition, "ExamplesDefinition" },
        { rule_type::examples, "Examples" },
        { rule_type::examples_table, "ExamplesTable" },
        { rule_type::step, "Step" },
        { rule_type::step_arg, "StepArg" },
        { rule_type::data_table, "DataTable" },
        { rule_type::doc_string, "DocString" },
        { rule_type::tags, "Tags" },
        { rule_type::description_helper, "DescriptionHelper" },
        { rule_type::description, "Description" }
    };

    return rmap.at(r);
}

}
