#include "cucumber/gherkin/ast_builder.hpp"
#include "cucumber/gherkin/exceptions.hpp"
#include "cucumber/gherkin/join_utils.hpp"
#include "cucumber/gherkin/regex.hpp"
#include "cucumber/messages/Step.hpp"
#include <iostream>
#include <optional>

namespace cucumber::gherkin
{

    ast_builder::ast_builder()
        : ast_builder(new_id_generator())
    {}

    ast_builder::ast_builder(id_generator_ptr idp)
        : idp_(idp)
    {}

    ast_builder::~ast_builder()
    {}

    void ast_builder::reset(std::string_view uri)
    {
        stack_ = {};
        stack_.emplace(rule_type::none);
        comments_.clear();
        uri_ = uri;
    }

    void ast_builder::start_rule(rule_type rule_type)
    {
        stack_.emplace(rule_type);
    }

    void ast_builder::end_rule(rule_type rule_type)
    {
        auto n = pop_node();
        auto rt = n.type();

        transform_node(n, current_node());
    }

    void ast_builder::build(const token& token)
    {
        if (token.matched_type == rule_type::comment)
        {
            cms::Comment c{ get_location(token), token.matched_text };

            comments_.emplace_back(std::make_shared<cms::Comment>(std::move(c)));
        }
        else
        {
            current_node().add(token.matched_type, token);
        }
    }

    const cms::GherkinDocument& ast_builder::get_result() const
    {
        auto dp = current_node().get_single<cms::GherkinDocument>(rule_type::gherkin_document);

        return dp ? *dp : doc_;
    };

    std::string ast_builder::next_id()
    {
        return idp_->next_id();
    }

    void ast_builder::transform_node(ast_node& from, ast_node& to)
    {
        if (from.is(rule_type::step))
        {
            to.add(from.type(), make_step(from));
        }
        else if (from.is(rule_type::doc_string))
        {
            to.add(from.type(), make_doc_string(from));
        }
        else if (from.is(rule_type::data_table))
        {
            to.add(from.type(), make_data_table(from));
        }
        else if (from.is(rule_type::background))
        {
            to.add(from.type(), make_background(from));
        }
        else if (from.is(rule_type::scenario_definition))
        {
            to.add(from.type(), make_scenario_definition(from));
        }
        else if (from.is(rule_type::examples_definition))
        {
            to.add(from.type(), make_examples_definition(from));
        }
        else if (from.is(rule_type::examples_table))
        {
            to.add(from.type(), make_examples_table(from));
        }
        else if (from.is(rule_type::description))
        {
            to.add(from.type(), make_description(from));
        }
        else if (from.is(rule_type::feature))
        {
            to.add(from.type(), make_feature(from));
        }
        else if (from.is(rule_type::rule))
        {
            to.add(from.type(), make_rule(from));
        }
        else if (from.is(rule_type::gherkin_document))
        {
            to.add(from.type(), make_gherkin_document(from));
        }
        else
        {
            to.add(from.type(), from);
        }
    }

    cms::Step ast_builder::make_step(ast_node& node)
    {
        auto& step_line = node.get_token(rule_type::step_line);

        cms::Step m{ get_location(step_line), step_line.matched_keyword.value_or(""), step_line.matched_keyword_type, step_line.matched_text, std::nullopt, std::nullopt, next_id() };

        node.set(rule_type::doc_string, m.docString);
        node.set(rule_type::data_table, m.dataTable);

        return m;
    }

    cms::DocString ast_builder::make_doc_string(ast_node& node)
    {
        auto& tokens = node.get_tokens(rule_type::doc_string_separator);
        auto& separator_token = tokens[0];

        string_views svs;

        for (const auto& t : node.get_tokens(rule_type::other))
        {
            svs.emplace_back(t.matched_text);
        }

        auto content = join("\n", svs);

        cms::DocString m{ get_location(separator_token), std::nullopt, content, separator_token.matched_keyword.value_or("") };

        if (!separator_token.matched_text.empty())
        {
            m.mediaType = separator_token.matched_text;
        }

        return m;
    }

    cms::DataTable ast_builder::make_data_table(ast_node& node)
    {
        auto rows = get_table_rows(node);

        cms::DataTable m;
        m.rows = std::move(rows);

        if (!m.rows.empty() && m.rows.front()->location)
        {
            m.location = m.rows.front()->location;
        }

        return m;
    }

    cms::Background ast_builder::make_background(ast_node& node)
    {
        auto& background_line = node.get_token(rule_type::background_line);

        cms::Background m{ get_location(background_line), background_line.matched_keyword.value_or(""), background_line.matched_text, {}, {}, next_id() };

        node.set(rule_type::description, m.description);
        node.set(rule_type::step, m.steps);

        return m;
    }

    cms::Scenario ast_builder::make_scenario_definition(ast_node& node)
    {
        auto pnode = node.get_single<ast_node>(rule_type::scenario);
        auto& scenario_node = *pnode;
        auto& scenario_line = scenario_node.get_token(rule_type::scenario_line);

        cms::Scenario m{ get_location(scenario_line), get_tags(node), scenario_line.matched_keyword.value_or(""), scenario_line.matched_text, {}, {}, {}, next_id() };

        scenario_node.set(rule_type::description, m.description);
        scenario_node.set(rule_type::step, m.steps);
        scenario_node.set(rule_type::examples_definition, m.examples);

        return m;
    }

    cms::Examples ast_builder::make_examples_definition(ast_node& node)
    {
        auto pnode = node.get_single<ast_node>(rule_type::examples);
        auto& examples_node = *pnode;
        auto& examples_line = examples_node.get_token(rule_type::examples_line);

        cms::Examples m{ get_location(examples_line), get_tags(node), examples_line.matched_keyword.value_or(""), examples_line.matched_text, {}, std::nullopt, {}, next_id() };

        examples_node.set(rule_type::description, m.description);

        auto prows = examples_node.get_single<table_rows>(rule_type::examples_table);

        if (prows)
        {
            auto& rows = *prows;

            m.tableHeader = rows.front();

            if (rows.size() > 1)
            {
                std::copy(rows.begin() + 1, rows.end(), std::back_inserter(m.tableBody));
            }
        }

        return m;
    }

    table_rows ast_builder::make_examples_table(ast_node& node)
    {
        return get_table_rows(node);
    }

    std::string ast_builder::make_description(ast_node& node)
    {
        static const std::regex only_spaces("\\s*");
        auto toks = node.get_tokens(rule_type::other);
        std::size_t ntoks = toks.size();

        while (ntoks && full_match(toks[ntoks - 1].matched_text, only_spaces))
        {
            --ntoks;
        }

        string_views svs;

        for (std::size_t i = 0; i < ntoks; ++i)
        {
            svs.emplace_back(toks[i].matched_text);
        }

        return join("\n", svs);
    }

    cms::Feature ast_builder::make_feature(ast_node& node)
    {
        auto pnode = node.get_single<ast_node>(rule_type::feature_header);
        auto& header = *pnode;

        auto ptoken = header.get_single<token>(rule_type::feature_line);
        auto& feature_line = *ptoken;

        cms::Feature m{ get_location(feature_line), get_tags(header), feature_line.matched_gherkin_dialect, feature_line.matched_keyword.value_or(""), feature_line.matched_text };

        header.set(rule_type::description, m.description);

        auto pb = node.get_single<cms::Background>(rule_type::background);

        if (pb)
        {
            cms::FeatureChild child;
            child.background = std::make_shared<cms::Background>(*pb);
            m.children.emplace_back(std::make_shared<cms::FeatureChild>(child));
        }

        auto ps = node.get_items<cms::Scenario>(rule_type::scenario_definition);

        if (ps)
        {
            for (auto& scenario : *ps)
            {
                cms::FeatureChild child;
                child.scenario = std::make_shared<cms::Scenario>(scenario);
                m.children.emplace_back(std::make_shared<cms::FeatureChild>(child));
            }
        }

        auto pr = node.get_items<cms::Rule>(rule_type::rule);

        if (pr)
        {
            for (auto& rule : *pr)
            {
                cms::FeatureChild child;
                child.rule = std::make_shared<cms::Rule>(rule);
                m.children.emplace_back(std::make_shared<cms::FeatureChild>(child));
            }
        }

        return m;
    }

    cms::Rule ast_builder::make_rule(ast_node& node)
    {
        auto pnode = node.get_single<ast_node>(rule_type::rule_header);
        auto& header = *pnode;

        auto ptoken = header.get_single<token>(rule_type::rule_line);
        auto& rule_line = *ptoken;

        cms::Rule m{ get_location(rule_line), get_tags(header), rule_line.matched_keyword.value_or(""), rule_line.matched_text, {}, {}, next_id() };

        header.set(rule_type::description, m.description);

        auto pb = node.get_single<cms::Background>(rule_type::background);

        if (pb)
        {
            cms::RuleChild child;
            child.background = std::make_shared<cms::Background>(*pb);
            m.children.emplace_back(std::make_shared<cms::RuleChild>(child));
        }

        auto ps = node.get_items<cms::Scenario>(rule_type::scenario_definition);

        if (ps)
        {
            for (auto& scenario : *ps)
            {
                cms::RuleChild child;
                child.scenario = std::make_shared<cms::Scenario>(scenario);
                m.children.emplace_back(std::make_shared<cms::RuleChild>(child));
            }
        }

        return m;
    }

    cms::GherkinDocument ast_builder::make_gherkin_document(ast_node& node)
    {
        cms::GherkinDocument gd{ std::string(uri_), std::nullopt, comments_ };

        node.set(rule_type::feature, gd.feature);

        return gd;
    }

    std::shared_ptr<cms::Location> ast_builder::get_location(const token& token, std::size_t column) const
    {
        std::size_t col = column == 0 ? token.location.column.value_or(0) : column;
        return std::make_shared<cms::Location>(cms::Location{ token.location.line, col > 0 ? std::optional(col) : std::nullopt });
    }

    table_rows ast_builder::get_table_rows(const ast_node& node)
    {
        table_rows rows;

        for (const auto& token : node.get_tokens(rule_type::table_row))
        {
            auto row = std::make_shared<cms::TableRow>();
            row->location = get_location(token);
            row->cells = get_table_cells(token);
            row->id = next_id();
            rows.emplace_back(row);
        }

        ensure_cell_count(rows);

        return rows;
    }

    void ast_builder::ensure_cell_count(const table_rows& rows) const
    {
        if (rows.empty())
        {
            return;
        }

        std::size_t cell_count = rows.front()->cells.size();

        for (const auto& row : rows)
        {
            if (row->cells.size() != cell_count)
            {
                throw ast_builder_error("inconsistent cell count within the table", { row->location->line, row->location->column.value_or(0) });
            }
        }
    }

    table_cells ast_builder::get_table_cells(const token& token)
    {
        table_cells cells;

        for (const auto& i : token.matched_items)
        {
            auto cell = std::make_shared<cms::TableCell>();
            cell->location = get_location(token, i.column);
            cell->value = i.text;
            cells.emplace_back(cell);
        }

        return cells;
    }

    tags ast_builder::get_tags(const ast_node& node)
    {
        tags ts;

        auto pnode = node.get_single<ast_node>(rule_type::tags);

        if (pnode)
        {
            auto& tags_node = *pnode;

            for (const auto& token : tags_node.get_tokens(rule_type::tag_line))
            {
                for (auto& tag_item : token.matched_items)
                {
                    cms::Tag t{ get_location(token, tag_item.column), tag_item.text, next_id() };

                    ts.emplace_back(std::make_shared<cms::Tag>(std::move(t)));
                }
            }
        }

        return ts;
    }

    ast_node ast_builder::pop_node()
    {
        ast_node n = std::move(current_node());

        stack_.pop();

        return n;
    }

    ast_node& ast_builder::current_node()
    {
        return stack_.top();
    }

    const ast_node& ast_builder::current_node() const
    {
        return stack_.top();
    }

}
