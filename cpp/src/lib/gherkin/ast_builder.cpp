#include <iostream>

#include <cucumber/messages/step.hpp>

#include <gherkin/ast_builder.hpp>
#include <gherkin/join_utils.hpp>

namespace gherkin {

ast_builder::ast_builder()
{
    reset();
}

ast_builder::~ast_builder()
{}

void
ast_builder::reset()
{
    stack_ = {};
    stack_.emplace(rule_type::none);
}

void
ast_builder::start_rule(rule_type rule_type)
{ stack_.emplace(rule_type); }

void
ast_builder::end_rule(rule_type rule_type)
{
    auto n = pop_node();
    auto rt = n.type();

    transform_node(n, current_node());
}

void
ast_builder::build(token& token)
{
    if (token.matched_type == rule_type::comment) {
        cms::comment c{
            .location = get_location(token),
            .text = token.matched_text
        };

        comments_.emplace_back(std::move(c));
    } else {
        current_node().add(token.matched_type, std::move(token));
    }
}

const cms::gherkin_document&
ast_builder::get_result() const
{
    return
        current_node().get_single<cms::gherkin_document>(
            rule_type::gherkin_document
        );
};

std::string
ast_builder::next_id()
{ return std::to_string(id_counter_++); }

void
ast_builder::transform_node(ast_node& from, ast_node& to)
{
    if (from.is(rule_type::step)) {
        to.add(from.type(), make_step(from));
    } else if (from.is(rule_type::doc_string)) {
        to.add(from.type(), make_doc_string(from));
    } else if (from.is(rule_type::data_table)) {
        to.add(from.type(), make_data_table(from));
    } else if (from.is(rule_type::background)) {
        to.add(from.type(), make_background(from));
    } else if (from.is(rule_type::scenario_definition)) {
        to.add(from.type(), make_scenario_definition(from));
    } else if (from.is(rule_type::examples_definition)) {
        to.add(from.type(), make_examples_definition(from));
    } else if (from.is(rule_type::examples_table)) {
        to.add(from.type(), make_examples_table(from));
    } else if (from.is(rule_type::description)) {
        to.add(from.type(), make_description(from));
    } else if (from.is(rule_type::feature)) {
        to.add(from.type(), make_feature(from));
    } else if (from.is(rule_type::rule)) {
        to.add(from.type(), make_rule(from));
    } else if (from.is(rule_type::gherkin_document)) {
        to.add(from.type(), make_gherkin_document(from));
    }
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
    auto& scenario_node = node.get_single<ast_node>(rule_type::scenario);
    auto& scenario_line = scenario_node.get_token(rule_type::scenario_line);

    cms::scenario s{
        .location = get_location(scenario_line),
        .tags = get_tags(node),
        .keyword = scenario_line.matched_keyword,
        .name = scenario_line.matched_text,
        .id = next_id()
    };

    scenario_node.set_from_single(rule_type::description, s.description);
    scenario_node.set_from_items(rule_type::step, s.steps);
    scenario_node.set_from_items(rule_type::examples_definition, s.examples);

    return s;
}

cms::examples
ast_builder::make_examples_definition(ast_node& node)
{
    auto& examples_node = node.get_single<ast_node>(rule_type::examples);
    auto& examples_line = examples_node.get_token(rule_type::examples_line);

    cms::examples es{
        .location = get_location(examples_line),
        .tags = get_tags(node),
        .keyword = examples_line.matched_keyword,
        .name = examples_line.matched_text,
        .id = next_id()
    };

    examples_node.set_from_single(rule_type::description, es.description);

    return es;
}

table_rows
ast_builder::make_examples_table(ast_node& node)
{ return get_table_rows(node); }

std::string
ast_builder::make_description(ast_node& node)
{
    return "FIXME";
}

cms::feature
ast_builder::make_feature(ast_node& node)
{
    auto& header = node.get_single<ast_node>(rule_type::feature_header);
    auto& feature_line = header.get_token(rule_type::feature_line);

    cms::feature f{
        .location = get_location(feature_line),
        .tags = get_tags(header),
        .keyword = feature_line.matched_keyword,
        .name = feature_line.matched_text
    };

    header.set_from_single(rule_type::description, f.description);

    return f;
}

cms::rule
ast_builder::make_rule(ast_node& node)
{
    auto& header = node.get_single<ast_node>(rule_type::rule_header);
    auto& rule_line = header.get_token(rule_type::rule_line);

    cms::rule r{
        .location = get_location(rule_line),
        .tags = get_tags(header),
        .keyword = rule_line.matched_keyword,
        .name = rule_line.matched_text,
        .id = next_id()
    };

    header.set_from_single(rule_type::description, r.description);

    return r;
}

cms::gherkin_document
ast_builder::make_gherkin_document(ast_node& node)
{
    cms::gherkin_document gd{
        .uri = uri_,
        .comments = comments_
    };

    node.set_from_single(rule_type::feature, gd.feature);

    return gd;
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

tags
ast_builder::get_tags(ast_node& node)
{
    tags ts;

    node.visit_item<ast_node>(
        rule_type::tags,
        [&](auto& tags_node) {
            auto& tokens = tags_node.get_tokens(rule_type::tag_line);

            for (auto& token : tokens) {
                for (auto& tag_item : token.matched_items) {
                    cms::tag t{
                        .location = get_location(token, tag_item.column),
                        .name = tag_item.text,
                        .id = next_id()
                    };

                    ts.emplace_back(std::move(t));
                }
            }
        }
    );

    return ts;
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
