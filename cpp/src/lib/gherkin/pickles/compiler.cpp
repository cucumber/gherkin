#include <gherkin/utils.hpp>
#include <gherkin/pickles/compiler.hpp>

namespace gherkin::pickles {

template <typename Vector>
void
append(Vector& to, const Vector& from)
{ to.insert(to.end(), from.begin(), from.end()); }

compiler::compiler()
{}

compiler::~compiler()
{}

pickles
compiler::compile(const cms::gherkin_document& d)
{
    pickles pickles;

    if (d.feature) {
        compile_feature(pickles, d.feature.value());
    }

    return pickles;
}

void
compiler::compile_feature(pickles& pickles, const cms::feature& f)
{
    auto tags = f.tags;
    steps background_steps;

    for (const auto& child : f.children) {
        if (child.background) {
            append(background_steps, child.background->steps);
        } else if (child.rule) {
            compile_rule(
                pickles,
                *child.rule,
                tags,
                background_steps
            );
        }
    }
}

void
compiler::compile_rule(
    pickles& pickles,
    const cms::rule& r,
    const tags& parent_tags,
    const steps& background_steps
)
{
    auto steps = background_steps;
    auto tags = parent_tags;

    append(tags, r.tags);

    for (const auto& child : r.children) {
        if (child.background) {
            append(steps, child.background->steps);
        } else if (child.scenario) {
            const auto& scenario = *child.scenario;

            if (scenario.examples.empty()) {
                compile_scenario(
                    pickles,
                    scenario,
                    tags,
                    steps
                );
            } else {
                compile_scenario_outline(
                    pickles,
                    scenario,
                    tags,
                    steps
                );
            }
        }
    }
}

void
compiler::compile_scenario(
    pickles& pickles,
    const cms::scenario& s,
    const tags& parent_tags,
    const steps& background_steps
)
{
    steps steps;

    if (!s.steps.empty()) {
        auto ssteps = background_steps;

        append(ssteps, s.steps);

        auto last_keyword_type = cms::step_keyword_type::UNKNOWN;

        for (const auto& step : ssteps) {
            if (step.keyword_type) {
                if (*step.keyword_type != cms::step_keyword_type::CONJUNCTION) {
                    last_keyword_type = *step.keyword_type;
                }
            }

            //steps.push_back()
        }
    }
}

cms::pickle_step
compiler::make_pickle_step(
    const cms::step& step,
    const table_cells& variable_cells,
    const cms::table_row* value_row_ptr,
    cms::step_keyword_type keyword_type
)
{
    const auto& value_cells =
        value_row_ptr
        ? value_row_ptr->cells
        : table_cells()
        ;

    auto step_text = interpolate(step.text, variable_cells, value_cells);
}

std::string
compiler::interpolate(
    const std::string& name,
    const table_cells& variable_cells,
    const table_cells& value_cells
)
{
    auto iname = name;
    std::size_t col = 0;
    std::string header;

    for (const auto& variable_cell : variable_cells) {
        const auto& value_cell = value_cells[col++];
        header = "<" + variable_cell.value + ">";

        replace(iname, header, value_cell.value);
    }

    return iname;
}

}
