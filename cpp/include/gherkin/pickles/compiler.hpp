#pragma once

#include <vector>

#include <cucumber/messages/all.hpp>

namespace gherkin::pickles {

namespace cms = cucumber::messages;

using pickles = std::vector<cms::pickle>;
using steps = std::vector<cms::step>;
using tags = std::vector<cms::tag>;
using table_cells = std::vector<cms::table_cell>;

class compiler
{
public:
    compiler();
    virtual ~compiler();

    pickles compile(const cms::gherkin_document& d);

private:
    void compile_feature(pickles& pickles, const cms::feature& f);

    void compile_rule(
        pickles& pickles,
        const cms::rule& r,
        const tags& parent_tags,
        const steps& background_steps
    );

    void compile_scenario(
        pickles& pickles,
        const cms::scenario& s,
        const tags& parent_tags,
        const steps& background_steps
    );

    void compile_scenario_outline(
        pickles& pickles,
        const cms::scenario& s,
        const tags& parent_tags,
        const steps& background_steps
    );

    cms::pickle_step make_pickle_step(
        const cms::step& step,
        const table_cells& variable_cells,
        const cms::table_row* value_row_ptr,
        cms::step_keyword_type keyword_type
    );

    std::string interpolate(
        const std::string& name,
        const table_cells& variable_cells,
        const table_cells& value_cells
    );
};

}
