#ifndef CUCUMBER_GHERKIN_PICKLE_COMPILER_HPP
#define CUCUMBER_GHERKIN_PICKLE_COMPILER_HPP

#include "cucumber/gherkin/cb_types.hpp"
#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/msg_types.hpp"
#include "cucumber/gherkin/pickle_compiler_context.hpp"
#include <cstddef>
#include <cucumber/messages/DataTable.hpp>
#include <cucumber/messages/DocString.hpp>
#include <cucumber/messages/Feature.hpp>
#include <cucumber/messages/GherkinDocument.hpp>
#include <cucumber/messages/PickleDocString.hpp>
#include <cucumber/messages/PickleStep.hpp>
#include <cucumber/messages/PickleTable.hpp>
#include <cucumber/messages/Rule.hpp>
#include <cucumber/messages/Scenario.hpp>
#include <cucumber/messages/Step.hpp>
#include <cucumber/messages/StepKeywordType.hpp>
#include <cucumber/messages/TableRow.hpp>
#include <optional>
#include <string>

namespace cucumber::gherkin
{

    class PickleCompiler
    {
    public:
        PickleCompiler();
        PickleCompiler(IdGeneratorPtr idp);

        virtual ~PickleCompiler() = default;
        PickleCompiler(const PickleCompiler&) = delete;
        PickleCompiler& operator=(const PickleCompiler&) = delete;
        PickleCompiler(PickleCompiler&&) = delete;
        PickleCompiler& operator=(PickleCompiler&&) = delete;

        Pickles Compile(const messages::GherkinDocument& document, const std::string& uri, PickleCb sink = {});

    private:
        void CompileFeature(PickleCompilerContext& context, const messages::Feature& feature, const std::string& language, const std::string& uri);

        void CompileRule(PickleCompilerContext& context, const messages::Rule& rule, const Tags& parentTags, const Steps& backgroundSteps, const std::string& language, const std::string& uri);

        void CompileScenario(
            PickleCompilerContext& context, const messages::Scenario& scenario, const Tags& parentTags, const Steps& backgroundSteps, const std::string& language, const std::string& uri);

        void CompileScenarioOutline(
            PickleCompilerContext& context, const messages::Scenario& scenario, const Tags& parentTags, const Steps& backgroundSteps, const std::string& language, const std::string& uri);

        static messages::PickleTable MakePickleTable(
            const std::optional<std::size_t>& argumentIndex, const messages::DataTable& dataTable, const TableCells& variableCells, const TableCells& valueCells);

        static messages::PickleDocString MakePickleDocString(
            const std::optional<std::size_t>& argumentIndex, const messages::DocString& docString, const TableCells& variableCells, const TableCells& valueCells);

        messages::PickleStep MakePickleStep(const messages::Step& step, const TableCells& variableCells, const messages::TableRow* valueRowPtr, messages::StepKeywordType keywordType);

        messages::PickleStep MakePickleStep(const messages::Step& step, messages::StepKeywordType keywordType);

        static PickleTags MakePickleTags(const Tags& tags);

        static std::string Interpolate(const std::string& name, const TableCells& variableCells, const TableCells& valueCells);

        std::string NextId();

        IdGeneratorPtr idp;
    };

}

#endif
