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
        PickleCompiler(id_generator_ptr idp);

        virtual ~PickleCompiler();
        PickleCompiler(const PickleCompiler&) = delete;
        PickleCompiler& operator=(const PickleCompiler&) = delete;
        PickleCompiler(PickleCompiler&&) = delete;
        PickleCompiler& operator=(PickleCompiler&&) = delete;

        pickles Compile(const cucumber::messages::GherkinDocument& document, const std::string& uri, pickle_cb sink = {});

    private:
        void CompileFeature(PickleCompilerContext& context, const cucumber::messages::Feature& feature, const std::string& language, const std::string& uri);

        void CompileRule(
            PickleCompilerContext& context, const cucumber::messages::Rule& rule, const tags& parentTags, const steps& backgroundSteps, const std::string& language, const std::string& uri);

        void CompileScenario(
            PickleCompilerContext& context, const cucumber::messages::Scenario& scenario, const tags& parentTags, const steps& backgroundSteps, const std::string& language, const std::string& uri);

        void CompileScenarioOutline(
            PickleCompilerContext& context, const cucumber::messages::Scenario& scenario, const tags& parentTags, const steps& backgroundSteps, const std::string& language, const std::string& uri);

        static cucumber::messages::PickleTable MakePickleTable(
            const std::optional<std::size_t>& argumentIndex, const cucumber::messages::DataTable& dataTable, const table_cells& variableCells, const table_cells& valueCells);

        static cucumber::messages::PickleDocString MakePickleDocString(
            const std::optional<std::size_t>& argumentIndex, const cucumber::messages::DocString& docString, const table_cells& variableCells, const table_cells& valueCells);

        cucumber::messages::PickleStep MakePickleStep(
            const cucumber::messages::Step& step, const table_cells& variableCells, const cucumber::messages::TableRow* valueRowPtr, cucumber::messages::StepKeywordType keywordType);

        cucumber::messages::PickleStep MakePickleStep(const cucumber::messages::Step& step, cucumber::messages::StepKeywordType keywordType);

        static pickle_tags MakePickleTags(const tags& tags);

        static std::string Interpolate(const std::string& name, const table_cells& variableCells, const table_cells& valueCells);

        std::string NextId();

        id_generator_ptr idp;
    };

}

#endif
