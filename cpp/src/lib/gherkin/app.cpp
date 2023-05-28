#include <gherkin/app.hpp>
#include <gherkin/utils.hpp>
#include <gherkin/pickle_compiler.hpp>

namespace gherkin {

app::app()
{}

app::~app()
{}

void
app::include_source(bool f)
{ include_source_ = f; }

void
app::include_ast(bool f)
{ include_ast_ = f; }

void
app::include_pickles(bool f)
{ include_pickles_ = f; }

void
app::parse(const file& f, const callbacks& cbs)
{
    cms::envelope e;

    e.source = cms::source{ .uri = f.path, .data = slurp(f.path) };

    parse(e, cbs);
}

void
app::parse(const cms::envelope& e, const callbacks& cbs)
{
    if (include_source_ && cbs.source) {
        cbs.source(*e.source);
    }

    parse(*e.source, cbs);
}

void
app::parse(const cms::source& s, const callbacks& cbs)
{
    auto ast = p_.parse(s.uri, s.data);

    if (include_ast_ && cbs.ast) {
        cbs.ast(ast);
    }

    if (include_pickles_ && cbs.pickle) {
        pickle_compiler pc;

        pc.compile(ast, s.uri, cbs.pickle);
    }
}

}
