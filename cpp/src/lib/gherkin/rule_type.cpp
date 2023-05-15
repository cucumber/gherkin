#include <unordered_map>

#include <gherkin/rule_type.hpp>

namespace gherkin {

std::string_view
to_string(rule_type r)
{
    static const std::unordered_map<rule_type, std::string_view> rmap = {
        { rule_type::none, "none" },
        { rule_type::e_o_f, "e_o_f" },
        { rule_type::empty, "empty" },
        { rule_type::comment, "comment" },
        { rule_type::tag_line, "tag_line" },
        { rule_type::feature_line, "feature_line" },
        { rule_type::rule_line, "rule_line" },
        { rule_type::background_line, "background_line" },
        { rule_type::scenario_line, "scenario_line" },
        { rule_type::examples_line, "examples_line" },
        { rule_type::step_line, "step_line" },
        { rule_type::doc_string_separator, "doc_string_separator" },
        { rule_type::table_row, "table_row" },
        { rule_type::language, "language" },
        { rule_type::other, "other" },
        { rule_type::gherkin_document, "gherkin_document" },
        { rule_type::feature, "feature" },
        { rule_type::feature_header, "feature_header" },
        { rule_type::rule, "rule" },
        { rule_type::rule_header, "rule_header" },
        { rule_type::background, "background" },
        { rule_type::scenario_definition, "scenario_definition" },
        { rule_type::scenario, "scenario" },
        { rule_type::examples_definition, "examples_definition" },
        { rule_type::examples, "examples" },
        { rule_type::examples_table, "examples_table" },
        { rule_type::step, "step" },
        { rule_type::step_arg, "step_arg" },
        { rule_type::data_table, "data_table" },
        { rule_type::doc_string, "doc_string" },
        { rule_type::tags, "tags" },
        { rule_type::description_helper, "description_helper" },
        { rule_type::description, "description" }
    };

    return rmap.at(r);
}

}
