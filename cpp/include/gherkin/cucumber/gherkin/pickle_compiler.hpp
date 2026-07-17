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

        pickles compile(const cms::GherkinDocument& document, const std::string& uri, pickle_cb sink = {});

    private:
        void compile_feature(PickleCompilerContext& context, const cms::Feature& feature, const std::string& language, const std::string& uri);

        void compile_rule(PickleCompilerContext& context, const cms::Rule& rule, const tags& parent_tags, const steps& background_steps, const std::string& language, const std::string& uri);

        void compile_scenario(
            PickleCompilerContext& context, const cms::Scenario& scenario, const tags& parent_tags, const steps& background_steps, const std::string& language, const std::string& uri);

        void compile_scenario_outline(
            PickleCompilerContext& context, const cms::Scenario& scenario, const tags& parent_tags, const steps& background_steps, const std::string& language, const std::string& uri);

        cms::PickleTable make_pickle_table(const std::optional<std::size_t>& argument_index, const cms::DataTable& data_table, const table_cells& variable_cells, const table_cells& value_cells);

        cms::PickleDocString make_pickle_doc_string(
            const std::optional<std::size_t>& argument_index, const cms::DocString& doc_string, const table_cells& variable_cells, const table_cells& value_cells);

        cms::PickleStep make_pickle_step(const cms::Step& step, const table_cells& variable_cells, const cms::TableRow* value_row_ptr, cms::StepKeywordType keyword_type);

        cms::PickleStep make_pickle_step(const cms::Step& step, cms::StepKeywordType keyword_type);

        pickle_tags make_pickle_tags(const tags& tags);

        std::string interpolate(const std::string& name, const table_cells& variable_cells, const table_cells& value_cells);

        std::string next_id();

        id_generator_ptr idp_;
    };

}

#endif
