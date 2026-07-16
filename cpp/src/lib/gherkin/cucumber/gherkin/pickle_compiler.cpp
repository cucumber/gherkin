#include "cucumber/gherkin/pickle_compiler.hpp"
#include "cucumber/gherkin/cb_types.hpp"
#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/msg_types.hpp"
#include "cucumber/gherkin/pickle_compiler_context.hpp"
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
#include <cstddef>
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
    void append(Vector& destination, const Vector& from)
    {
        destination.insert(destination.end(), from.begin(), from.end());
    }

    PickleCompiler::PickleCompiler()
        : PickleCompiler(new_id_generator())
    {}

    PickleCompiler::PickleCompiler(id_generator_ptr idp)
        : idp_(idp)
    {}

    PickleCompiler::~PickleCompiler()
    {}

    pickles PickleCompiler::compile(const cms::GherkinDocument& document, const std::string& uri, pickle_cb sink)
    {
        PickleCompilerContext context{ idp_, sink };

        if (document.feature)
        {
            compile_feature(context, *document.feature.value(), document.feature.value()->language, uri);
        }

        return context.pickles;
    }

    void PickleCompiler::compile_feature(PickleCompilerContext& context, const cms::Feature& feature, const std::string& language, const std::string& uri)
    {
        auto tags = feature.tags;
        steps background_steps;

        for (const auto& child : feature.children)
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
                compile_rule(context, *child->rule.value(), tags, background_steps, language, uri);
            }
            else if (child->scenario)
            {
                const auto& scenario = *child->scenario.value();

                if (scenario.examples.empty())
                {
                    compile_scenario(context, scenario, tags, background_steps, language, uri);
                }
                else
                {
                    compile_scenario_outline(context, scenario, tags, background_steps, language, uri);
                }
            }
        }
    }

    void PickleCompiler::compile_rule(
        PickleCompilerContext& context, const cms::Rule& rule, const tags& parent_tags, const steps& background_steps, const std::string& language, const std::string& uri)
    {
        auto steps = background_steps;
        auto tags = parent_tags;

        for (const auto& tag : rule.tags)
        {
            tags.push_back(tag);
        }

        for (const auto& child : rule.children)
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
                    compile_scenario(context, scenario, tags, steps, language, uri);
                }
                else
                {
                    compile_scenario_outline(context, scenario, tags, steps, language, uri);
                }
            }
        }
    }

    void PickleCompiler::compile_scenario(
        PickleCompilerContext& context, const cms::Scenario& scenario, const tags& parent_tags, const steps& background_steps, const std::string& language, const std::string& uri)
    {
        auto conjunction = cms::StepKeywordType::CONJUNCTION;
        pickle_steps steps;

        if (!scenario.steps.empty())
        {
            auto all_steps = background_steps;

            for (const auto& step : scenario.steps)
            {
                all_steps.push_back(step);
            }

            auto last_keyword_type = cms::StepKeywordType::UNKNOWN;

            for (const auto& step : all_steps)
            {
                if (step->keywordType && *step->keywordType != conjunction)
                {
                    last_keyword_type = *step->keywordType;
                }

                steps.push_back(std::make_shared<cms::PickleStep>(make_pickle_step(*step, last_keyword_type)));
            }
        }

        auto tags = parent_tags;

        for (const auto& tag : scenario.tags)
        {
            tags.push_back(tag);
        }

        strings source_ids = { scenario.id };

        cms::Pickle pickle{ context.next_id(), uri, scenario.location, scenario.name, language, steps, make_pickle_tags(tags), source_ids };

        context.add_pickle(pickle);
    }

    void PickleCompiler::compile_scenario_outline(
        PickleCompilerContext& context, const cms::Scenario& scenario, const tags& parent_tags, const steps& background_steps, const std::string& language, const std::string& uri)
    {
        auto conjunction = cms::StepKeywordType::CONJUNCTION;

        for (const auto& example : scenario.examples)
        {
            if (!example->tableHeader)
            {
                continue;
            }

            const auto& variable_cells = example->tableHeader.value()->cells;
            const auto& table_body = example->tableBody;

            for (const auto& values_row : table_body)
            {
                const auto& value_cells = values_row->cells;

                pickle_steps steps;
                auto last_keyword_type = cms::StepKeywordType::UNKNOWN;

                if (!scenario.steps.empty())
                {
                    for (const auto& step : background_steps)
                    {
                        if (step->keywordType && *step->keywordType != conjunction)
                        {
                            last_keyword_type = *step->keywordType;
                        }

                        steps.push_back(std::make_shared<cms::PickleStep>(make_pickle_step(*step, last_keyword_type)));
                    }
                }

                auto tags = parent_tags;

                for (const auto& tag : scenario.tags)
                {
                    tags.push_back(tag);
                }
                for (const auto& tag : example->tags)
                {
                    tags.push_back(tag);
                }

                for (const auto& step : scenario.steps)
                {
                    if (step->keywordType && *step->keywordType != conjunction)
                    {
                        last_keyword_type = *step->keywordType;
                    }

                    steps.push_back(std::make_shared<cms::PickleStep>(make_pickle_step(*step, variable_cells, std::addressof(*values_row), last_keyword_type)));
                }

                strings source_ids = { scenario.id, values_row->id };

                cms::Pickle pickle{ context.next_id(), uri, values_row->location, interpolate(scenario.name, variable_cells, value_cells), language, steps, make_pickle_tags(tags), source_ids };

                context.add_pickle(pickle);
            }
        }
    }

    cms::PickleStep PickleCompiler::make_pickle_step(const cms::Step& step, const table_cells& variable_cells, const cms::TableRow* value_row_ptr, cms::StepKeywordType keyword_type)
    {
        const auto& value_cells = value_row_ptr ? value_row_ptr->cells : table_cells();

        cms::PickleStep pickle_step{ std::nullopt, { step.id }, next_id(), to_pickle_step_type(keyword_type), interpolate(step.text, variable_cells, value_cells) };

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
            pickle_step.argument = std::move(arg);
        }

        if (value_row_ptr)
        {
            pickle_step.astNodeIds.push_back(value_row_ptr->id);
        }

        return pickle_step;
    }

    cms::PickleTable PickleCompiler::make_pickle_table(
        const std::optional<std::size_t>& argument_index, const cms::DataTable& data_table, const table_cells& variable_cells, const table_cells& value_cells)
    {
        cms::PickleTable pickle_table{ argument_index };

        for (const auto& row : data_table.rows)
        {
            auto pickle_row = std::make_shared<cms::PickleTableRow>();

            for (const auto& cell : row->cells)
            {
                auto pickle_cell = std::make_shared<cms::PickleTableCell>();
                pickle_cell->value = interpolate(cell->value, variable_cells, value_cells);
                pickle_row->cells.emplace_back(pickle_cell);
            }

            pickle_table.rows.emplace_back(std::move(pickle_row));
        }

        return pickle_table;
    }

    cms::PickleDocString PickleCompiler::make_pickle_doc_string(
        const std::optional<std::size_t>& argument_index, const cms::DocString& doc_string, const table_cells& variable_cells, const table_cells& value_cells)
    {
        cms::PickleDocString pickle_doc_string{ argument_index, std::nullopt, interpolate(doc_string.content, variable_cells, value_cells) };

        if (doc_string.mediaType)
        {
            pickle_doc_string.mediaType = interpolate(*doc_string.mediaType, variable_cells, value_cells);
        }

        return pickle_doc_string;
    }

    cms::PickleStep PickleCompiler::make_pickle_step(const cms::Step& step, cms::StepKeywordType keyword_type)
    {
        return make_pickle_step(step, {}, nullptr, keyword_type);
    }

    pickle_tags PickleCompiler::make_pickle_tags(const tags& tags)
    {
        pickle_tags result_tags;

        for (const auto& source_tag : tags)
        {
            auto pickle_tag = std::make_shared<cms::PickleTag>();
            pickle_tag->name = source_tag->name;
            pickle_tag->astNodeId = source_tag->id;
            result_tags.emplace_back(pickle_tag);
        }

        return result_tags;
    }

    std::string PickleCompiler::interpolate(const std::string& name, const table_cells& variable_cells, const table_cells& value_cells)
    {
        auto interpolated_name = name;
        std::size_t col = 0;
        std::string header;

        for (const auto& variable_cell : variable_cells)
        {
            const auto& value_cell = value_cells[col++];
            header = "<" + variable_cell->value + ">";

            replace(interpolated_name, header, value_cell->value);
        }

        return interpolated_name;
    }

    std::string PickleCompiler::next_id()
    {
        return idp_->next_id();
    }

}
