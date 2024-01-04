#pragma once

#include <vector>

#include <cucumber/gherkin/types.hpp>
#include <cucumber/gherkin/msg_types.hpp>
#include <cucumber/gherkin/cb_types.hpp>
#include <cucumber/gherkin/pickle_compiler_context.hpp>
#include <cucumber/gherkin/id_generator.hpp>

namespace cucumber::gherkin {

class pickle_compiler
{
public:
    pickle_compiler();
    pickle_compiler(id_generator_ptr idp);

    virtual ~pickle_compiler();

    pickles compile(
        const cms::gherkin_document& d,
        const std::string& uri,
        pickle_cb sink = {}
    );

private:
    void compile_feature(
        pickle_compiler_context& ctx,
        const cms::feature& f,
        const std::string& language,
        const std::string& uri
    );

    void compile_rule(
        pickle_compiler_context& ctx,
        const cms::rule& r,
        const tags& parent_tags,
        const steps& background_steps,
        const std::string& language,
        const std::string& uri
    );

    void compile_scenario(
        pickle_compiler_context& ctx,
        const cms::scenario& s,
        const tags& parent_tags,
        const steps& background_steps,
        const std::string& language,
        const std::string& uri
    );

    void compile_scenario_outline(
        pickle_compiler_context& ctx,
        const cms::scenario& s,
        const tags& parent_tags,
        const steps& background_steps,
        const std::string& language,
        const std::string& uri
    );

    cms::pickle_table make_pickle_table(
        const cms::data_table& dt,
        const table_cells& variable_cells,
        const table_cells& value_cells
    );

    cms::pickle_doc_string make_pickle_doc_string(
        const cms::doc_string& ds,
        const table_cells& variable_cells,
        const table_cells& value_cells
    );

    cms::pickle_step make_pickle_step(
        const cms::step& step,
        const table_cells& variable_cells,
        const cms::table_row* value_row_ptr,
        cms::step_keyword_type keyword_type
    );

    cms::pickle_step make_pickle_step(
        const cms::step& step,
        cms::step_keyword_type keyword_type
    );

    pickle_tags make_pickle_tags(const tags& tags);

    std::string interpolate(
        const std::string& name,
        const table_cells& variable_cells,
        const table_cells& value_cells
    );

    std::string next_id();

    id_generator_ptr idp_;
};

}
