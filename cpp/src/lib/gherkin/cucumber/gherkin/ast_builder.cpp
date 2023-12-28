#include <iostream>

#include <cucumber/messages/step.hpp>

#include <cucumber/gherkin/ast_builder.hpp>
#include <cucumber/gherkin/join_utils.hpp>
#include <cucumber/gherkin/regex.hpp>
#include <cucumber/gherkin/exceptions.hpp>

namespace cucumber::gherkin {

ast_builder::ast_builder()
: ast_builder(new_id_generator())
{}

ast_builder::ast_builder(id_generator_ptr idp)
: idp_(idp)
{}

ast_builder::~ast_builder()
{}

void
ast_builder::reset(std::string_view uri)
{
    stack_ = {};
    stack_.emplace(rule_type::none);
    comments_.clear();
    uri_ = uri;
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
ast_builder::build(const token& token)
{
    if (token.matched_type == rule_type::comment) {
        cms::comment c{
            .location = get_location(token),
            .text = token.matched_text
        };

        comments_.emplace_back(std::move(c));
    } else {
        current_node().add(token.matched_type, token);
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
{ return idp_->next_id(); }

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
    } else {
        to.add(from.type(), from);
    }
}

cms::step
ast_builder::make_step(ast_node& node)
{
    auto& step_line = node.get_token(rule_type::step_line);

    cms::step m{
        .location = get_location(step_line),
        .keyword = step_line.matched_keyword.value_or(""),
        .keyword_type = step_line.matched_keyword_type,
        .text = step_line.matched_text,
        .id = next_id()
    };

    node.set(rule_type::doc_string, m.doc_string);
    node.set(rule_type::data_table, m.data_table);

    return m;
}

cms::doc_string
ast_builder::make_doc_string(ast_node& node)
{
    auto& tokens = node.get_tokens(rule_type::doc_string_separator);
    auto& separator_token = tokens[0];

    string_views svs;

    for (const auto& t : node.get_tokens(rule_type::other)) {
        svs.emplace_back(t.matched_text);
    }

    auto content = join("\n", svs);

    cms::doc_string m{
        .location = get_location(separator_token),
        .content = content,
        .delimiter = separator_token.matched_keyword.value_or("")
    };

    if (!separator_token.matched_text.empty()) {
        m.media_type = separator_token.matched_text;
    }

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
        m.location = m.rows.front().location;
    }

    return m;
}

cms::background
ast_builder::make_background(ast_node& node)
{
    auto& background_line = node.get_token(rule_type::background_line);

    cms::background m{
        .location = get_location(background_line),
        .keyword = background_line.matched_keyword.value_or(""),
        .name = background_line.matched_text,
        .id = next_id()
    };

    node.set(rule_type::description, m.description);
    node.set(rule_type::step, m.steps);

    return m;
}

cms::scenario
ast_builder::make_scenario_definition(ast_node& node)
{
    auto pnode = node.get_single<ast_node>(rule_type::scenario);
    auto& scenario_node = *pnode;
    auto& scenario_line = scenario_node.get_token(rule_type::scenario_line);

    cms::scenario m{
        .location = get_location(scenario_line),
        .tags = get_tags(node),
        .keyword = scenario_line.matched_keyword.value_or(""),
        .name = scenario_line.matched_text,
        .id = next_id()
    };

    scenario_node.set(rule_type::description, m.description);
    scenario_node.set(rule_type::step, m.steps);
    scenario_node.set(rule_type::examples_definition, m.examples);

    return m;
}

cms::examples
ast_builder::make_examples_definition(ast_node& node)
{
    auto pnode = node.get_single<ast_node>(rule_type::examples);
    auto& examples_node = *pnode;
    auto& examples_line = examples_node.get_token(rule_type::examples_line);

    cms::examples m{
        .location = get_location(examples_line),
        .tags = get_tags(node),
        .keyword = examples_line.matched_keyword.value_or(""),
        .name = examples_line.matched_text,
        .id = next_id()
    };

    examples_node.set(rule_type::description, m.description);

    auto prows = examples_node.get_single<table_rows>(
        rule_type::examples_table
    );

    if (prows) {
        auto& rows = *prows;

        m.table_header = rows.front();

        if (rows.size() > 1) {
            std::copy(
                rows.begin() + 1, rows.end(),
                std::back_inserter(m.table_body)
                );
        }
    }

    return m;
}

table_rows
ast_builder::make_examples_table(ast_node& node)
{ return get_table_rows(node); }

std::string
ast_builder::make_description(ast_node& node)
{
    std::regex only_spaces("\\s*");
    auto toks = node.get_tokens(rule_type::other);
    std::size_t ntoks = toks.size();

    while (
        ntoks
        &&
        full_match(toks[ntoks - 1].matched_text, only_spaces)
    ) {
        --ntoks;
    }

    string_views svs;

    for (std::size_t i = 0; i < ntoks; ++i) {
        svs.emplace_back(toks[i].matched_text);
    }

    return join("\n", svs);
}

cms::feature
ast_builder::make_feature(ast_node& node)
{
    auto pnode = node.get_single<ast_node>(rule_type::feature_header);
    auto& header = *pnode;

    auto ptoken = header.get_single<token>(rule_type::feature_line);
    auto& feature_line = *ptoken;

    cms::feature m{
        .location = get_location(feature_line),
        .tags = get_tags(header),
        .language = feature_line.matched_gherkin_dialect,
        .keyword = feature_line.matched_keyword.value_or(""),
        .name = feature_line.matched_text
    };

    header.set(rule_type::description, m.description);

    auto pb = node.get_single<cms::background>(rule_type::background);

    if (pb) {
        m.children.emplace_back(cms::feature_child{ .background = *pb });
    }

    auto ps = node.get_items<cms::scenario>(rule_type::scenario_definition);

    if (ps) {
        for (auto& scenario : *ps) {
            m.children.emplace_back(cms::feature_child{.scenario = scenario});
        }
    }

    auto pr = node.get_items<cms::rule>(rule_type::rule);

    if (pr) {
        for (auto& rule : *pr) {
            m.children.emplace_back(cms::feature_child{.rule = rule});
        }
    }

    return m;
}

cms::rule
ast_builder::make_rule(ast_node& node)
{
    auto pnode = node.get_single<ast_node>(rule_type::rule_header);
    auto& header = *pnode;

    auto ptoken = header.get_single<token>(rule_type::rule_line);
    auto& rule_line = *ptoken;

    cms::rule m{
        .location = get_location(rule_line),
        .tags = get_tags(header),
        .keyword = rule_line.matched_keyword.value_or(""),
        .name = rule_line.matched_text,
        .id = next_id()
    };

    header.set(rule_type::description, m.description);

    auto pb = node.get_single<cms::background>(rule_type::background);

    if (pb) {
        m.children.emplace_back(cms::rule_child{ .background = *pb });
    }

    auto ps = node.get_items<cms::scenario>(rule_type::scenario_definition);

    if (ps) {
        for (auto& scenario : *ps) {
            m.children.emplace_back(cms::rule_child{.scenario = scenario});
        }
    }

    return m;
}

cms::gherkin_document
ast_builder::make_gherkin_document(ast_node& node)
{
    cms::gherkin_document gd{
        .uri = std::string(uri_),
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
    cms::location m{
        .line = token.location.line,
        .column = column == 0 ? token.location.column : column
    };

    return m;
}

table_rows
ast_builder::get_table_rows(const ast_node& node)
{
    table_rows rows;

    for (const auto& token : node.get_tokens(rule_type::table_row)) {
        rows.emplace_back(cms::table_row{
            .location = get_location(token),
            .cells = get_table_cells(token),
            .id = next_id()
        });
    }

    ensure_cell_count(rows);

    return rows;
}

void
ast_builder::ensure_cell_count(const table_rows& rows) const
{
    if (rows.empty()) {
        return;
    }

    std::size_t cell_count = rows.front().cells.size();

    for (const auto& row : rows) {
        if (row.cells.size() != cell_count) {
            throw
                ast_builder_error(
                    "inconsistent cell count within the table",
                    {
                        .line = row.location.line,
                        .column = row.location.column.value_or(0)
                    }
                );
        }
    }
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

    auto pnode = node.get_single<ast_node>(rule_type::tags);

    if (pnode) {
        auto& tags_node = *pnode;

        for (const auto& token : tags_node.get_tokens(rule_type::tag_line)) {
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
