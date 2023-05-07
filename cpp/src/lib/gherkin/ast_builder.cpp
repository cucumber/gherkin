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

node_item
ast_builder::transform_node(ast_node& node)
{
    if (node.is(rule_type::step)) {
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

        return make_node_item(s);
    } else if (node.is(rule_type::doc_string)) {
        auto& separator_token =
            node.get_first_token(rule_type::doc_string_separator);

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

        return make_node_item(ds);
    } else if (node.is(rule_type::data_table)) {
        auto rows = get_table_rows(node);

        cms::data_table dt{
            .location = rows.front().location,
            .rows = std::move(rows)
        };

        return make_node_item(dt);
    }

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
