#include <cucumber/gherkin/utils.hpp>
#include <cucumber/gherkin/regex.hpp>
#include <cucumber/gherkin/pickle_compiler.hpp>

namespace cucumber::gherkin {

cms::pickle_step_type
to_pickle_step_type(cms::step_keyword_type keyword_type)
{
    using step_map_type = std::unordered_map<
        cms::step_keyword_type,
        cms::pickle_step_type
    >;

    static const step_map_type smap = {
        { cms::step_keyword_type::UNKNOWN, cms::pickle_step_type::UNKNOWN },
        { cms::step_keyword_type::CONTEXT, cms::pickle_step_type::CONTEXT },
        { cms::step_keyword_type::ACTION, cms::pickle_step_type::ACTION },
        { cms::step_keyword_type::OUTCOME, cms::pickle_step_type::OUTCOME }
    };

    return smap.at(keyword_type);
}

template <typename Vector>
void
append(Vector& to, const Vector& from)
{ to.insert(to.end(), from.begin(), from.end()); }

pickle_compiler::pickle_compiler()
: pickle_compiler(new_id_generator())
{}

pickle_compiler::pickle_compiler(id_generator_ptr idp)
: idp_(idp)
{}

pickle_compiler::~pickle_compiler()
{}

pickles
pickle_compiler::compile(
    const cms::gherkin_document& d,
    const std::string& uri,
    pickle_cb sink
)
{
    pickle_compiler_context ctx{ .idp = idp_, .sink = sink };

    if (d.feature) {
        compile_feature(ctx, *d.feature, d.feature->language, uri);
    }

    return ctx.pickles;
}

void
pickle_compiler::compile_feature(
    pickle_compiler_context& ctx,
    const cms::feature& f,
    const std::string& language,
    const std::string& uri
)
{
    auto tags = f.tags;
    steps background_steps;

    for (const auto& child : f.children) {
        if (child.background) {
            append(background_steps, child.background->steps);
        } else if (child.rule) {
            compile_rule(
                ctx,
                *child.rule,
                tags,
                background_steps,
                language,
                uri
            );
        } else if (child.scenario) {
            const auto& scenario = *child.scenario;

            if (scenario.examples.empty()) {
                compile_scenario(
                    ctx,
                    scenario,
                    tags,
                    background_steps,
                    language,
                    uri
                );
            } else {
                compile_scenario_outline(
                    ctx,
                    scenario,
                    tags,
                    background_steps,
                    language,
                    uri
                );
            }
        }
    }
}

void
pickle_compiler::compile_rule(
    pickle_compiler_context& ctx,
    const cms::rule& r,
    const tags& parent_tags,
    const steps& background_steps,
    const std::string& language,
    const std::string& uri
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
                    ctx,
                    scenario,
                    tags,
                    steps,
                    language,
                    uri
                );
            } else {
                compile_scenario_outline(
                    ctx,
                    scenario,
                    tags,
                    steps,
                    language,
                    uri
                );
            }
        }
    }
}

void
pickle_compiler::compile_scenario(
    pickle_compiler_context& ctx,
    const cms::scenario& s,
    const tags& parent_tags,
    const steps& background_steps,
    const std::string& language,
    const std::string& uri
)
{
    auto conj = cms::step_keyword_type::CONJUNCTION;
    pickle_steps steps;

    if (!s.steps.empty()) {
        auto ssteps = background_steps;

        append(ssteps, s.steps);

        auto last_keyword_type = cms::step_keyword_type::UNKNOWN;

        for (const auto& step : ssteps) {
            if (step.keyword_type && *step.keyword_type != conj) {
                last_keyword_type = *step.keyword_type;
            }

            steps.push_back(make_pickle_step(step, last_keyword_type));
        }
    }

    auto tags = parent_tags;

    append(tags, s.tags);

    strings source_ids = { s.id };

    cms::pickle p{
        .id = ctx.next_id(),
        .uri = uri,
        .name = s.name,
        .language = language,
        .steps = steps,
        .tags = make_pickle_tags(tags),
        .ast_node_ids = source_ids
    };

    ctx.add_pickle(p);
}

void
pickle_compiler::compile_scenario_outline(
    pickle_compiler_context& ctx,
    const cms::scenario& s,
    const tags& parent_tags,
    const steps& background_steps,
    const std::string& language,
    const std::string& uri
)
{
    auto conj = cms::step_keyword_type::CONJUNCTION;

    for (const auto& es : s.examples) {
        if (!es.table_header) {
            continue;
        }

        const auto& variable_cells = es.table_header->cells;

        for (const auto& values_row : es.table_body) {
            const auto& value_cells = values_row.cells;

            pickle_steps steps;
            auto last_keyword_type = cms::step_keyword_type::UNKNOWN;

            if (!s.steps.empty()) {
                for (const auto& step : background_steps) {
                    if (step.keyword_type && *step.keyword_type != conj) {
                        last_keyword_type = *step.keyword_type;
                    }

                    steps.push_back(make_pickle_step(step, last_keyword_type));
                }
            }

            auto tags = parent_tags;

            append(tags, s.tags);
            append(tags, es.tags);

            for (const auto& step : s.steps) {
                if (step.keyword_type && *step.keyword_type != conj) {
                    last_keyword_type = *step.keyword_type;
                }

                steps.push_back(
                    make_pickle_step(
                        step,
                        variable_cells,
                        std::addressof(values_row),
                        last_keyword_type
                    )
                );
            }

            strings source_ids = { s.id, values_row.id };

            cms::pickle p{
                .id = ctx.next_id(),
                .uri = uri,
                .name = interpolate(s.name, variable_cells, value_cells),
                .language = language,
                .steps = steps,
                .tags = make_pickle_tags(tags),
                .ast_node_ids = source_ids
            };

            ctx.add_pickle(p);
        }
    }
}

cms::pickle_step
pickle_compiler::make_pickle_step(
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

    cms::pickle_step ps{
        .ast_node_ids = { step.id },
        .id = next_id(),
        .type = to_pickle_step_type(keyword_type),
        .text = interpolate(step.text, variable_cells, value_cells)
    };

    if (step.data_table) {
        ps.argument = cms::pickle_step_argument{
            .data_table = make_pickle_table(
                *step.data_table,
                variable_cells,
                value_cells
            )
        };
    } else if (step.doc_string) {
        ps.argument = cms::pickle_step_argument{
            .doc_string = make_pickle_doc_string(
                *step.doc_string,
                variable_cells,
                value_cells
            )
        };
    }

    if (value_row_ptr) {
        ps.ast_node_ids.push_back(value_row_ptr->id);
    }

    return ps;
}

cms::pickle_table
pickle_compiler::make_pickle_table(
    const cms::data_table& dt,
    const table_cells& variable_cells,
    const table_cells& value_cells
)
{
    cms::pickle_table t;

    for (const auto& row : dt.rows) {
        cms::pickle_table_row r;

        for (const auto& cell : row.cells) {
            r.cells.emplace_back(cms::pickle_table_cell{
                .value = interpolate(
                    cell.value,
                    variable_cells,
                    value_cells
                )
            });
        }

        t.rows.emplace_back(std::move(r));
    }

    return t;
}

cms::pickle_doc_string
pickle_compiler::make_pickle_doc_string(
    const cms::doc_string& ds,
    const table_cells& variable_cells,
    const table_cells& value_cells
)
{
    cms::pickle_doc_string pds{
        .content = interpolate(ds.content, variable_cells, value_cells)
    };

    if (ds.media_type) {
        pds.media_type = interpolate(
            *ds.media_type,
            variable_cells,
            value_cells
        );
    }

    return pds;
}

cms::pickle_step
pickle_compiler::make_pickle_step(
    const cms::step& step,
    cms::step_keyword_type keyword_type
)
{ return make_pickle_step(step, {}, nullptr, keyword_type); }

pickle_tags
pickle_compiler::make_pickle_tags(const tags& tags)
{
    pickle_tags ptags;

    std::transform(
        tags.cbegin(), tags.cend(),
        std::back_inserter(ptags),
        [](const auto& t) {
            return
                cms::pickle_tag{
                    .name = t.name,
                    .ast_node_id = t.id
                };
        }
    );

    return ptags;
}

std::string
pickle_compiler::interpolate(
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

std::string
pickle_compiler::next_id()
{ return idp_->next_id(); }

}
