#include "cucumber/gherkin/pickle_compiler.hpp"
#include "cucumber/gherkin/cb_types.hpp"
#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/msg_types.hpp"
#include "cucumber/gherkin/pickle_compiler_context.hpp"
#include "cucumber/gherkin/regex.hpp"
#include "cucumber/gherkin/types.hpp"
#include "cucumber/gherkin/utils.hpp"
#include "cucumber/messages/DataTable.hpp"
#include "cucumber/messages/DocString.hpp"
#include "cucumber/messages/Feature.hpp"
#include "cucumber/messages/GherkinDocument.hpp"
#include "cucumber/messages/Pickle.hpp"
#include "cucumber/messages/PickleDocString.hpp"
#include "cucumber/messages/PickleStep.hpp"
#include "cucumber/messages/PickleStepArgument.hpp"
#include "cucumber/messages/PickleStepType.hpp"
#include "cucumber/messages/PickleTable.hpp"
#include "cucumber/messages/PickleTableCell.hpp"
#include "cucumber/messages/PickleTableRow.hpp"
#include "cucumber/messages/PickleTag.hpp"
#include "cucumber/messages/Rule.hpp"
#include "cucumber/messages/Scenario.hpp"
#include "cucumber/messages/Step.hpp"
#include "cucumber/messages/StepKeywordType.hpp"
#include "cucumber/messages/TableRow.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

namespace cucumber::gherkin
{

    cms::PickleStepType to_pickle_step_type(cms::StepKeywordType keyword_type)
    {
        using step_map_type = std::unordered_map<cms::StepKeywordType, cms::PickleStepType>;

        static const step_map_type smap = { { cms::StepKeywordType::UNKNOWN, cms::PickleStepType::UNKNOWN }, { cms::StepKeywordType::CONTEXT, cms::PickleStepType::CONTEXT },
            { cms::StepKeywordType::ACTION, cms::PickleStepType::ACTION }, { cms::StepKeywordType::OUTCOME, cms::PickleStepType::OUTCOME } };

        return smap.at(keyword_type);
    }

    template<typename Vector>
    void append(Vector& to, const Vector& from)
    {
        to.insert(to.end(), from.begin(), from.end());
    }

    pickle_compiler::pickle_compiler()
        : pickle_compiler(new_id_generator())
    {}

    pickle_compiler::pickle_compiler(id_generator_ptr idp)
        : idp_(idp)
    {}

    pickle_compiler::~pickle_compiler()
    {}

    pickles pickle_compiler::compile(const cms::GherkinDocument& d, const std::string& uri, pickle_cb sink)
    {
        pickle_compiler_context ctx{ idp_, sink };

        if (d.feature)
        {
            compile_feature(ctx, *d.feature.value(), d.feature.value()->language, uri);
        }

        return ctx.pickles;
    }

    void pickle_compiler::compile_feature(pickle_compiler_context& ctx, const cms::Feature& f, const std::string& language, const std::string& uri)
    {
        auto tags = f.tags;
        steps background_steps;

        for (const auto& child : f.children)
        {
            if (child->background)
            {
                const auto& background_steps_temp = child->background.value()->steps;
                for (const auto& step : background_steps_temp)
                {
                    background_steps.push_back(step);
                }
            }
            else if (child->rule)
            {
                compile_rule(ctx, *child->rule.value(), tags, background_steps, language, uri);
            }
            else if (child->scenario)
            {
                const auto& scenario = *child->scenario.value();

                if (scenario.examples.empty())
                {
                    compile_scenario(ctx, scenario, tags, background_steps, language, uri);
                }
                else
                {
                    compile_scenario_outline(ctx, scenario, tags, background_steps, language, uri);
                }
            }
        }
    }

    void pickle_compiler::compile_rule(pickle_compiler_context& ctx, const cms::Rule& r, const tags& parent_tags, const steps& background_steps, const std::string& language, const std::string& uri)
    {
        auto steps = background_steps;
        auto tags = parent_tags;

        for (const auto& tag : r.tags)
        {
            tags.push_back(tag);
        }

        for (const auto& child : r.children)
        {
            if (child->background)
            {
                const auto& background_steps_temp = child->background.value()->steps;
                for (const auto& step : background_steps_temp)
                {
                    steps.push_back(step);
                }
            }
            else if (child->scenario)
            {
                const auto& scenario = *child->scenario.value();

                if (scenario.examples.empty())
                {
                    compile_scenario(ctx, scenario, tags, steps, language, uri);
                }
                else
                {
                    compile_scenario_outline(ctx, scenario, tags, steps, language, uri);
                }
            }
        }
    }

    void pickle_compiler::compile_scenario(
        pickle_compiler_context& ctx, const cms::Scenario& s, const tags& parent_tags, const steps& background_steps, const std::string& language, const std::string& uri)
    {
        auto conj = cms::StepKeywordType::CONJUNCTION;
        pickle_steps steps;

        if (!s.steps.empty())
        {
            auto ssteps = background_steps;

            for (const auto& step : s.steps)
            {
                ssteps.push_back(step);
            }

            auto last_keyword_type = cms::StepKeywordType::UNKNOWN;

            for (const auto& step : ssteps)
            {
                if (step->keywordType && *step->keywordType != conj)
                {
                    last_keyword_type = *step->keywordType;
                }

                steps.push_back(std::make_shared<cms::PickleStep>(make_pickle_step(*step, last_keyword_type)));
            }
        }

        auto tags = parent_tags;

        for (const auto& tag : s.tags)
        {
            tags.push_back(tag);
        }

        strings source_ids = { s.id };

        cms::Pickle p{ ctx.next_id(), uri, s.location, s.name, language, steps, make_pickle_tags(tags), source_ids };

        ctx.add_pickle(p);
    }

    void pickle_compiler::compile_scenario_outline(
        pickle_compiler_context& ctx, const cms::Scenario& s, const tags& parent_tags, const steps& background_steps, const std::string& language, const std::string& uri)
    {
        auto conj = cms::StepKeywordType::CONJUNCTION;

        for (const auto& es : s.examples)
        {
            if (!es->tableHeader)
            {
                continue;
            }

            const auto& variable_cells = es->tableHeader.value()->cells;
            const auto& table_body = es->tableBody;

            for (const auto& values_row : table_body)
            {
                const auto& value_cells = values_row->cells;

                pickle_steps steps;
                auto last_keyword_type = cms::StepKeywordType::UNKNOWN;

                if (!s.steps.empty())
                {
                    for (const auto& step : background_steps)
                    {
                        if (step->keywordType && *step->keywordType != conj)
                        {
                            last_keyword_type = *step->keywordType;
                        }

                        steps.push_back(std::make_shared<cms::PickleStep>(make_pickle_step(*step, last_keyword_type)));
                    }
                }

                auto tags = parent_tags;

                for (const auto& tag : s.tags)
                {
                    tags.push_back(tag);
                }
                for (const auto& tag : es->tags)
                {
                    tags.push_back(tag);
                }

                for (const auto& step : s.steps)
                {
                    if (step->keywordType && *step->keywordType != conj)
                    {
                        last_keyword_type = *step->keywordType;
                    }

                    steps.push_back(std::make_shared<cms::PickleStep>(make_pickle_step(*step, variable_cells, std::addressof(*values_row), last_keyword_type)));
                }

                strings source_ids = { s.id, values_row->id };

                cms::Pickle p{ ctx.next_id(), uri, values_row->location, interpolate(s.name, variable_cells, value_cells), language, steps, make_pickle_tags(tags), source_ids };

                ctx.add_pickle(p);
            }
        }
    }

    cms::PickleStep pickle_compiler::make_pickle_step(const cms::Step& step, const table_cells& variable_cells, const cms::TableRow* value_row_ptr, cms::StepKeywordType keyword_type)
    {
        const auto& value_cells = value_row_ptr ? value_row_ptr->cells : table_cells();

        cms::PickleStep ps{ std::nullopt, { step.id }, next_id(), to_pickle_step_type(keyword_type), interpolate(step.text, variable_cells, value_cells) };

        std::optional<std::size_t> data_table_argument_index = {};
        std::optional<std::size_t> doc_string_argument_index = {};
        if (step.dataTable && step.docString)
        {
            if (step.docString.value()->location->line > step.dataTable.value()->location->line)
            {
                data_table_argument_index = 1;
                doc_string_argument_index = 2;
            }
            else
            {
                data_table_argument_index = 2;
                doc_string_argument_index = 1;
            }
        }

        if (step.dataTable || step.docString)
        {
            auto arg = std::make_shared<cms::PickleStepArgument>();
            if (step.docString)
            {
                arg->docString = std::make_shared<cms::PickleDocString>(make_pickle_doc_string(doc_string_argument_index, *step.docString.value(), variable_cells, value_cells));
            }
            if (step.dataTable)
            {
                arg->dataTable = std::make_shared<cms::PickleTable>(make_pickle_table(data_table_argument_index, *step.dataTable.value(), variable_cells, value_cells));
            }
            ps.argument = std::move(arg);
        }

        if (value_row_ptr)
        {
            ps.astNodeIds.push_back(value_row_ptr->id);
        }

        return ps;
    }

    cms::PickleTable pickle_compiler::make_pickle_table(const std::optional<std::size_t>& argument_index, const cms::DataTable& dt, const table_cells& variable_cells, const table_cells& value_cells)
    {
        cms::PickleTable t{ argument_index };

        for (const auto& row : dt.rows)
        {
            auto r = std::make_shared<cms::PickleTableRow>();

            for (const auto& cell : row->cells)
            {
                auto pc = std::make_shared<cms::PickleTableCell>();
                pc->value = interpolate(cell->value, variable_cells, value_cells);
                r->cells.emplace_back(pc);
            }

            t.rows.emplace_back(std::move(r));
        }

        return t;
    }

    cms::PickleDocString pickle_compiler::make_pickle_doc_string(
        const std::optional<std::size_t>& argument_index, const cms::DocString& ds, const table_cells& variable_cells, const table_cells& value_cells)
    {
        cms::PickleDocString pds{ argument_index, std::nullopt, interpolate(ds.content, variable_cells, value_cells) };

        if (ds.mediaType)
        {
            pds.mediaType = interpolate(*ds.mediaType, variable_cells, value_cells);
        }

        return pds;
    }

    cms::PickleStep pickle_compiler::make_pickle_step(const cms::Step& step, cms::StepKeywordType keyword_type)
    {
        return make_pickle_step(step, {}, nullptr, keyword_type);
    }

    pickle_tags pickle_compiler::make_pickle_tags(const tags& tags)
    {
        pickle_tags ptags;

        for (const auto& t : tags)
        {
            auto pt = std::make_shared<cms::PickleTag>();
            pt->name = t->name;
            pt->astNodeId = t->id;
            ptags.emplace_back(pt);
        }

        return ptags;
    }

    std::string pickle_compiler::interpolate(const std::string& name, const table_cells& variable_cells, const table_cells& value_cells)
    {
        auto iname = name;
        std::size_t col = 0;
        std::string header;

        for (const auto& variable_cell : variable_cells)
        {
            const auto& value_cell = value_cells[col++];
            header = "<" + variable_cell->value + ">";

            replace(iname, header, value_cell->value);
        }

        return iname;
    }

    std::string pickle_compiler::next_id()
    {
        return idp_->next_id();
    }

}
