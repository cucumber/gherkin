#pragma once

#include <vector>

#include <gherkin/types.hpp>
#include <gherkin/msg_types.hpp>

namespace gherkin {

class pickle_compiler
{
public:
    pickle_compiler();
    virtual ~pickle_compiler();

    pickles compile(
        const cms::gherkin_document& d,
        const std::string& uri
    );

private:
    void compile_feature(
        pickles& pickles,
        const cms::feature& f,
        const std::string& language,
        const std::string& uri
    );

    void compile_rule(
        pickles& pickles,
        const cms::rule& r,
        const tags& parent_tags,
        const steps& background_steps,
        const std::string& language,
        const std::string& uri
    );

    void compile_scenario(
        pickles& pickles,
        const cms::scenario& s,
        const tags& parent_tags,
        const steps& background_steps,
        const std::string& language,
        const std::string& uri
    );

    void compile_scenario_outline(
        pickles& pickles,
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

    std::size_t id_counter_ = 0;
};

}