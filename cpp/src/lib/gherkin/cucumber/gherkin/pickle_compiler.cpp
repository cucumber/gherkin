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

// NOLINTBEGIN(bugprone-unchecked-optional-access)
namespace cucumber::gherkin
{

    messages::PickleStepType ToPickleStepType(messages::StepKeywordType keywordType)
    {
        using step_map_type = std::unordered_map<messages::StepKeywordType, messages::PickleStepType>;

        static const step_map_type smap = { { messages::StepKeywordType::UNKNOWN, messages::PickleStepType::UNKNOWN }, { messages::StepKeywordType::CONTEXT, messages::PickleStepType::CONTEXT },
            { messages::StepKeywordType::ACTION, messages::PickleStepType::ACTION }, { messages::StepKeywordType::OUTCOME, messages::PickleStepType::OUTCOME } };

        return smap.at(keywordType);
    }

    template<typename Vector>
    void Append(Vector& destination, const Vector& from)
    {
        destination.insert(destination.end(), from.begin(), from.end());
    }

    PickleCompiler::PickleCompiler()
        : PickleCompiler(NewIdGenerator())
    {}

    PickleCompiler::PickleCompiler(id_generator_ptr idp)
        : idp(std::move(std::move(idp)))
    {}

    PickleCompiler::~PickleCompiler() = default;

    Pickles PickleCompiler::Compile(const messages::GherkinDocument& document, const std::string& uri, pickle_cb sink)
    {
        PickleCompilerContext context{ idp, std::move(sink) };

        if (document.feature)
        {
            CompileFeature(context, *document.feature.value(), document.feature.value()->language, uri);
        }

        return context.pickles;
    }

    void PickleCompiler::CompileFeature(PickleCompilerContext& context, const messages::Feature& feature, const std::string& language, const std::string& uri)
    {
        auto tags = feature.tags;
        Steps backgroundSteps;

        for (const auto& child : feature.children)
        {
            if (child->background)
            {
                const auto& backgroundStepsTemp = child->background.value()->steps;
                for (const auto& step : backgroundStepsTemp)
                {
                    backgroundSteps.push_back(step);
                }
            }
            else if (child->rule)
            {
                CompileRule(context, *child->rule.value(), tags, backgroundSteps, language, uri);
            }
            else if (child->scenario)
            {
                const auto& scenario = *child->scenario.value();

                if (scenario.examples.empty())
                {
                    CompileScenario(context, scenario, tags, backgroundSteps, language, uri);
                }
                else
                {
                    CompileScenarioOutline(context, scenario, tags, backgroundSteps, language, uri);
                }
            }
        }
    }

    void PickleCompiler::CompileRule(
        PickleCompilerContext& context, const messages::Rule& rule, const Tags& parentTags, const Steps& backgroundSteps, const std::string& language, const std::string& uri)
    {
        auto steps = backgroundSteps;
        auto tags = parentTags;

        for (const auto& tag : rule.tags)
        {
            tags.push_back(tag);
        }

        for (const auto& child : rule.children)
        {
            if (child->background)
            {
                const auto& backgroundStepsTemp = child->background.value()->steps;
                for (const auto& step : backgroundStepsTemp)
                {
                    steps.push_back(step);
                }
            }
            else if (child->scenario)
            {
                const auto& scenario = *child->scenario.value();

                if (scenario.examples.empty())
                {
                    CompileScenario(context, scenario, tags, steps, language, uri);
                }
                else
                {
                    CompileScenarioOutline(context, scenario, tags, steps, language, uri);
                }
            }
        }
    }

    void PickleCompiler::CompileScenario(
        PickleCompilerContext& context, const messages::Scenario& scenario, const Tags& parentTags, const Steps& backgroundSteps, const std::string& language, const std::string& uri)
    {
        auto conjunction = messages::StepKeywordType::CONJUNCTION;
        PickleSteps steps;

        if (!scenario.steps.empty())
        {
            auto allSteps = backgroundSteps;

            for (const auto& step : scenario.steps)
            {
                allSteps.push_back(step);
            }

            auto lastKeywordType = messages::StepKeywordType::UNKNOWN;

            for (const auto& step : allSteps)
            {
                if (step->keywordType && *step->keywordType != conjunction)
                {
                    lastKeywordType = *step->keywordType;
                }

                steps.push_back(std::make_shared<messages::PickleStep>(MakePickleStep(*step, lastKeywordType)));
            }
        }

        auto tags = parentTags;

        for (const auto& tag : scenario.tags)
        {
            tags.push_back(tag);
        }

        strings const sourceIds = { scenario.id };

        messages::Pickle pickle{ context.NextId(), uri, scenario.location, scenario.name, language, steps, MakePickleTags(tags), sourceIds };

        context.AddPickle(pickle);
    }

    // NOLINTNEXTLINE(readability-function-cognitive-complexity)
    void PickleCompiler::CompileScenarioOutline(
        PickleCompilerContext& context, const messages::Scenario& scenario, const Tags& parentTags, const Steps& backgroundSteps, const std::string& language, const std::string& uri)
    {
        auto conjunction = messages::StepKeywordType::CONJUNCTION;

        for (const auto& example : scenario.examples)
        {
            if (!example->tableHeader)
            {
                continue;
            }

            const auto& variableCells = example->tableHeader.value()->cells;
            const auto& tableBody = example->tableBody;

            for (const auto& valuesRow : tableBody)
            {
                const auto& valueCells = valuesRow->cells;

                PickleSteps steps;
                auto lastKeywordType = messages::StepKeywordType::UNKNOWN;

                if (!scenario.steps.empty())
                {
                    for (const auto& step : backgroundSteps)
                    {
                        if (step->keywordType && *step->keywordType != conjunction)
                        {
                            lastKeywordType = *step->keywordType;
                        }

                        steps.push_back(std::make_shared<messages::PickleStep>(MakePickleStep(*step, lastKeywordType)));
                    }
                }

                auto tags = parentTags;

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
                        lastKeywordType = *step->keywordType;
                    }

                    steps.push_back(std::make_shared<messages::PickleStep>(MakePickleStep(*step, variableCells, std::addressof(*valuesRow), lastKeywordType)));
                }

                strings const sourceIds = { scenario.id, valuesRow->id };

                messages::Pickle pickle{ context.NextId(), uri, valuesRow->location, Interpolate(scenario.name, variableCells, valueCells), language, steps, MakePickleTags(tags), sourceIds };

                context.AddPickle(pickle);
            }
        }
    }

    messages::PickleStep PickleCompiler::MakePickleStep(const messages::Step& step, const TableCells& variableCells, const messages::TableRow* valueRowPtr, messages::StepKeywordType keywordType)
    {
        const auto& valueCells = (valueRowPtr != nullptr) ? valueRowPtr->cells : TableCells();

        messages::PickleStep pickleStep{ std::nullopt, { step.id }, NextId(), ToPickleStepType(keywordType), Interpolate(step.text, variableCells, valueCells) };

        std::optional<std::size_t> dataTableArgumentIndex = {};
        std::optional<std::size_t> docStringArgumentIndex = {};
        if (step.dataTable && step.docString)
        {
            if (step.docString.value()->location->line > step.dataTable.value()->location->line)
            {
                dataTableArgumentIndex = 1;
                docStringArgumentIndex = 2;
            }
            else
            {
                dataTableArgumentIndex = 2;
                docStringArgumentIndex = 1;
            }
        }

        if (step.dataTable || step.docString)
        {
            auto arg = std::make_shared<messages::PickleStepArgument>();
            if (step.docString)
            {
                arg->docString = std::make_shared<messages::PickleDocString>(MakePickleDocString(docStringArgumentIndex, *step.docString.value(), variableCells, valueCells));
            }
            if (step.dataTable)
            {
                arg->dataTable = std::make_shared<messages::PickleTable>(MakePickleTable(dataTableArgumentIndex, *step.dataTable.value(), variableCells, valueCells));
            }
            pickleStep.argument = std::move(arg);
        }

        if (valueRowPtr != nullptr)
        {
            pickleStep.astNodeIds.push_back(valueRowPtr->id);
        }

        return pickleStep;
    }

    messages::PickleTable PickleCompiler::MakePickleTable(
        const std::optional<std::size_t>& argumentIndex, const messages::DataTable& dataTable, const TableCells& variableCells, const TableCells& valueCells)
    {
        messages::PickleTable pickleTable{ argumentIndex };

        for (const auto& row : dataTable.rows)
        {
            auto pickleRow = std::make_shared<messages::PickleTableRow>();

            for (const auto& cell : row->cells)
            {
                auto pickleCell = std::make_shared<messages::PickleTableCell>();
                pickleCell->value = Interpolate(cell->value, variableCells, valueCells);
                pickleRow->cells.emplace_back(pickleCell);
            }

            pickleTable.rows.emplace_back(std::move(pickleRow));
        }

        return pickleTable;
    }

    messages::PickleDocString PickleCompiler::MakePickleDocString(
        const std::optional<std::size_t>& argumentIndex, const messages::DocString& docString, const TableCells& variableCells, const TableCells& valueCells)
    {
        messages::PickleDocString pickleDocString{ argumentIndex, std::nullopt, Interpolate(docString.content, variableCells, valueCells) };

        if (docString.mediaType)
        {
            pickleDocString.mediaType = Interpolate(*docString.mediaType, variableCells, valueCells);
        }

        return pickleDocString;
    }

    messages::PickleStep PickleCompiler::MakePickleStep(const messages::Step& step, messages::StepKeywordType keywordType)
    {
        return MakePickleStep(step, {}, nullptr, keywordType);
    }

    PickleTags PickleCompiler::MakePickleTags(const Tags& tags)
    {
        PickleTags resultTags;

        for (const auto& sourceTag : tags)
        {
            auto pickleTag = std::make_shared<messages::PickleTag>();
            pickleTag->name = sourceTag->name;
            pickleTag->astNodeId = sourceTag->id;
            resultTags.emplace_back(pickleTag);
        }

        return resultTags;
    }

    std::string PickleCompiler::Interpolate(const std::string& name, const TableCells& variableCells, const TableCells& valueCells) // NOLINT(bugprone-easily-swappable-parameters)
    {
        auto interpolatedName = name;
        std::size_t col = 0;
        std::string header;

        for (const auto& variableCell : variableCells)
        {
            const auto& valueCell = valueCells[col++];
            header = "<" + variableCell->value + ">";

            Replace(interpolatedName, header, valueCell->value);
        }

        return interpolatedName;
    }

    std::string PickleCompiler::NextId()
    {
        return idp->NextId();
    }

}

// NOLINTEND(bugprone-unchecked-optional-access)
