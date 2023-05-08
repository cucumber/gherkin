#include <cucumber/messages/step.hpp>

#include <gherkin/ast_builder.hpp>
#include <gherkin/join_utils.hpp>

namespace gherkin {

ast_builder::ast_builder()
{}

ast_builder::~ast_builder()
{}

void
ast_builder::reset()
{}

void
ast_builder::start_rule(rule_type rule_type)
{ stack_.emplace(rule_type); }

void
ast_builder::end_rule(rule_type rule_type)
{
    auto n = pop_node();
    auto rt = n.type();
    auto p = transform_node(n);

    current_node().add(rt, std::move(p));
}

void
build(token& token)
{}

std::string
ast_builder::next_id()
{ return std::to_string(id_counter_++); }

ast_node
ast_builder::transform_node(ast_node& node)
{
    if (node.is(rule_type::step)) {
        make_step(node);
    } else if (node.is(rule_type::doc_string)) {
        make_doc_string(node);
    } else if (node.is(rule_type::data_table)) {
        make_data_table(node);
    } else if (node.is(rule_type::background)) {
        make_background(node);
    } else if (node.is(rule_type::scenario_definition)) {
        make_scenario_definition(node);
    } else if (node.is(rule_type::examples_definition)) {
        make_examples_definition(node);
    } else if (node.is(rule_type::examples_table)) {
        make_examples_table(node);
    } else if (node.is(rule_type::description)) {
        make_description(node);
    } else if (node.is(rule_type::feature)) {
        make_feature(node);
    } else if (node.is(rule_type::rule)) {
        make_rule(node);
    } else if (node.is(rule_type::gherkin_document)) {
        make_gherkin_document(node);
    }

    return ast_node(rule_type::none);
}

cms::step
ast_builder::make_step(ast_node& node)
{
    auto& step_line = node.get_token(rule_type::step_line);

    cms::step s{
        .location = get_location(step_line),
        .keyword = step_line.matched_keyword,
        .keyword_type = step_line.matched_keyword_type,
        .text = step_line.matched_text,
        .id = next_id()
    };

    node.set_from_single(rule_type::doc_string, s.doc_string);
    node.set_from_single(rule_type::data_table, s.data_table);

    return s;
}

cms::doc_string
ast_builder::make_doc_string(ast_node& node)
{
    auto& separator_token = node.get_token(rule_type::doc_string_separator);

    string_views svs;

    for (const auto& t : node.get_tokens(rule_type::other)) {
        svs.push_back(t.matched_text);
    }

    cms::doc_string ds{
        .location = get_location(separator_token),
        .media_type = separator_token.matched_text,
        .content = join("\n", svs),
        .delimiter = separator_token.matched_keyword
    };

    return ds;
}

cms::data_table
ast_builder::make_data_table(ast_node& node)
{
    auto rows = get_table_rows(node);

    cms::data_table dt{
        .location = rows.front().location,
        .rows = std::move(rows)
    };

    return dt;
}

cms::background
ast_builder::make_background(ast_node& node)
{
    auto& background_line = node.get_token(rule_type::background_line);

    cms::background b{
        .location = get_location(background_line),
        .keyword = background_line.matched_keyword,
        .name = background_line.matched_text,
        .id = next_id()
    };

    node.set_from_single(rule_type::description, b.description);
    node.set_from_items(rule_type::step, b.steps);

    return b;
}

cms::scenario
ast_builder::make_scenario_definition(ast_node& node)
{
    return {};
}

cms::examples
ast_builder::make_examples_definition(ast_node& node)
{
    return {};
}

table_rows
ast_builder::make_examples_table(ast_node& node)
{
    return {};
}

std::string
ast_builder::make_description(ast_node& node)
{
    return {};
}

cms::feature
ast_builder::make_feature(ast_node& node)
{
    return {};
}

cms::rule
ast_builder::make_rule(ast_node& node)
{
    return {};
}

cms::gherkin_document
ast_builder::make_gherkin_document(ast_node& node)
{
    return {};
}

cms::location
ast_builder::get_location(
    const token& token,
    std::size_t column
) const
{
    return {};
}

table_rows
ast_builder::get_table_rows(ast_node& node)
{
    table_rows rows;

    for (const auto& t : node.get_tokens(rule_type::table_row)) {
        cms::table_row row{
            .location = get_location(t),
            .cells = get_table_cells(t),
            .id = next_id()
        };

        rows.emplace_back(std::move(row));
    }

    return rows;
}

table_cells
ast_builder::get_table_cells(const token& token)
{
    table_cells cells;

    for (const auto& i : token.matched_items) {
        cms::table_cell cell{
            .location = get_location(token, i.column),
            .value = i.text
        };

        cells.emplace_back(std::move(cell));
    }

    return cells;
}

ast_node
ast_builder::pop_node()
{
    ast_node n = std::move(current_node());

    stack_.pop();

    return n;
}

ast_node&
ast_builder::current_node()
{ return stack_.top(); }

const ast_node&
ast_builder::current_node() const
{ return stack_.top(); }

}
