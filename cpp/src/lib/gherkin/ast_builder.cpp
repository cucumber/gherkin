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
    auto dp = current_node().get_single<cms::gherkin_document>(
        rule_type::gherkin_document
    );

    return dp ? *dp : doc_;
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
    cms::step m{};

    node.visit_token(
        rule_type::step_line,
        [&](auto& step_line) {
            m.location = get_location(step_line);
            m.keyword = step_line.matched_keyword;
            m.keyword_type = step_line.matched_keyword_type;
            m.text = step_line.matched_text;
            m.id = next_id();
        }
    );

    node.set(rule_type::doc_string, m.doc_string);
    node.set(rule_type::data_table, m.data_table);

    return m;
}

cms::doc_string
ast_builder::make_doc_string(ast_node& node)
{
    cms::doc_string m{};

    node.visit_token(
        rule_type::doc_string_separator,
        [&](auto& separator_token) {
            string_views svs;

            node.visit_tokens(
                rule_type::other,
                [&](auto& line_tokens) {
                    for (const auto& t : line_tokens) {
                        svs.push_back(t.matched_text);
                    }
                }
            );

            m.location = get_location(separator_token);
            m.media_type = separator_token.matched_text;
            m.content = join("\n", svs);
            m.delimiter = separator_token.matched_keyword;
        }
    );

    return m;
}

cms::data_table
ast_builder::make_data_table(ast_node& node)
{
    auto rows = get_table_rows(node);

    cms::data_table m{
        .rows = std::move(rows)
    };

    if (!m.rows.empty()) {
        m.location = rows.front().location;
    }

    return m;
}

cms::background
ast_builder::make_background(ast_node& node)
{
    cms::background m{};

    node.visit_token(
        rule_type::background_line,
        [&](auto& background_line) {
            m.location = get_location(background_line);
            m.keyword = background_line.matched_keyword;
            m.name = background_line.matched_text;
            m.id = next_id();
        }
    );

    node.set(rule_type::description, m.description);
    node.set(rule_type::step, m.steps);

    return m;
}

cms::scenario
ast_builder::make_scenario_definition(ast_node& node)
{
    cms::scenario m{};

    node.visit_item<ast_node>(
        rule_type::scenario,
        [&](auto& scenario_node) {
            scenario_node.visit_token(
                rule_type::scenario_line,
                [&](auto& scenario_line) {
                    m.location = get_location(scenario_line);
                    m.tags = get_tags(node);
                    m.keyword = scenario_line.matched_keyword;
                    m.name = scenario_line.matched_text;
                    m.id = next_id();
                }
            );

            scenario_node.set(rule_type::description, m.description);
            scenario_node.set(rule_type::step, m.steps);
            scenario_node.set(rule_type::examples_definition, m.examples);
        }
    );

    return m;
}

cms::examples
ast_builder::make_examples_definition(ast_node& node)
{
    cms::examples m{};

    node.visit_item<ast_node>(
        rule_type::examples,
        [&](auto& examples_node) {
            examples_node.visit_token(
                rule_type::examples_line,
                [&](auto& examples_line) {
                    m.location = get_location(examples_line);
                    m.tags = get_tags(node);
                    m.keyword = examples_line.matched_keyword;
                    m.name = examples_line.matched_text;
                    m.id = next_id();
                }
            );

            examples_node.set(rule_type::description, m.description);

            examples_node.template visit_items<cms::table_row>(
                rule_type::examples_table,
                [&](auto& rows) {
                    if (rows.size() > 0) {
                        m.table_header = rows.front();
                    }

                    if (rows.size() > 1) {
                        std::copy(
                            rows.begin() + 1, rows.end(),
                            std::back_inserter(m.table_body)
                        );
                    }
                }
            );
        }
    );

    return m;
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
    cms::feature m{};

    node.visit_item<ast_node>(
        rule_type::feature_header,
        [&](auto& header) {
            header.visit_token(
                rule_type::feature_line,
                [&](auto& feature_line) {
                    m.location = get_location(feature_line);
                    m.tags = get_tags(header);
                    m.keyword = feature_line.matched_keyword;
                    m.name = feature_line.matched_text;
                }
            );

            header.set(rule_type::description, m.description);
        }
    );

    node.visit_item<cms::background>(
        rule_type::background,
        [&](auto& item) {
            m.children.emplace_back(cms::feature_child{.background = item});
        }
    );

    node.visit_items<cms::scenario>(
        rule_type::scenario_definition,
        [&](auto& items) {
            for (auto& item : items) {
                m.children.emplace_back(cms::feature_child{.scenario = item});
            }
        }
    );

    node.visit_items<cms::rule>(
        rule_type::rule,
        [&](auto& items) {
            for (auto& item : items) {
                m.children.emplace_back(cms::feature_child{.rule = item});
            }
        }
    );

    return m;
}

cms::rule
ast_builder::make_rule(ast_node& node)
{
    cms::rule m{};

    node.visit_item<ast_node>(
        rule_type::rule_header,
        [&](auto& header) {
            header.visit_token(
                rule_type::rule_line,
                [&](auto& rule_line) {
                    m.location = get_location(rule_line);
                    m.tags = get_tags(header);
                    m.keyword = rule_line.matched_keyword;
                    m.name = rule_line.matched_text;
                    m.id = next_id();
                }
            );

            header.set(rule_type::description, m.description);
        }
    );

    node.visit_item<cms::background>(
        rule_type::background,
        [&](auto& item) {
            m.children.emplace_back(cms::rule_child{.background = item});
        }
    );

    node.visit_items<cms::scenario>(
        rule_type::scenario_definition,
        [&](auto& items) {
            for (auto& item : items) {
                m.children.emplace_back(cms::rule_child{.scenario = item});
            }
        }
    );

    return m;
}

cms::gherkin_document
ast_builder::make_gherkin_document(ast_node& node)
{
    cms::gherkin_document gd{
        .uri = uri_,
        .comments = comments_
    };

    node.set(rule_type::feature, gd.feature);

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
ast_builder::get_table_rows(const ast_node& node)
{
    table_rows rows;

    node.visit_tokens(
        rule_type::table_row,
        [&](auto& tokens) {
            for (const auto& t : tokens) {
                rows.emplace_back(cms::table_row{
                    .location = get_location(t),
                    .cells = get_table_cells(t),
                    .id = next_id()
                });

            }
        }
    );

    return rows;
}

table_cells
ast_builder::get_table_cells(const token& token)
{
    table_cells cells;

    for (const auto& i : token.matched_items) {
        cells.emplace_back(cms::table_cell{
            .location = get_location(token, i.column),
            .value = i.text
        });
    }

    return cells;
}

tags
ast_builder::get_tags(const ast_node& node)
{
    tags ts;

    node.visit_item<ast_node>(
        rule_type::tags,
        [&](auto& tags_node) {
            tags_node.visit_tokens(
                rule_type::tag_line,
                [&](auto& tokens) {
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
