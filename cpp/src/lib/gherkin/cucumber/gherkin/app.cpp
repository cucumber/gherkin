#include <cucumber/gherkin/app.hpp>
#include <cucumber/gherkin/utils.hpp>
#include <cucumber/gherkin/pickle_compiler.hpp>
#include <cucumber/gherkin/exceptions.hpp>

namespace cucumber::gherkin {

app::app()
: idp_(new_id_generator()),
p_(idp_)
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
    try {
        auto ast = p_.parse(s.uri, s.data);

        if (include_ast_ && cbs.ast) {
            cbs.ast(ast);
        }

        if (include_pickles_ && cbs.pickle) {
            pickle_compiler pc(idp_);

            pc.compile(ast, s.uri, cbs.pickle);
        }
    } catch (const composite_parser_error& e) {
        for (const auto& ep : e.errors()) {
            send_parse_error(s.uri, *ep, cbs);
        }
    } catch (const parser_error& e) {
        send_parse_error(s.uri, e, cbs);
    }
}

void
app::send_parse_error(
    const std::string& uri,
    const parser_error& e,
    const callbacks& cbs
) const
{
    parse_error pe{
        .uri = uri,
        .location = e.location(),
        .message = e.what()
    };

    call_cb(cbs.error, pe);
}

}
