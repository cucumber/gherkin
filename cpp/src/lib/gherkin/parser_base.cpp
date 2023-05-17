#include <gherkin/utils.hpp>

#include <gherkin/parser_base.hpp>
#include <gherkin/pickle_compiler.hpp>

namespace gherkin {

parser_base::parser_base(const parser_info& pi)
: pi_(pi)
{}

parser_base::~parser_base()
{}

data
parser_base::parse(const std::string& data)
{ return parse_from_source({ .data = data }); }

data
parser_base::parse(const gherkin::file& file)
{
    return parse_from_source({
        .uri = file.path,
        .data = slurp(file.path)
    });
}

void
parser_base::reset(const cms::source& source)
{
    builder_.reset(source.uri);
    scanner_.reset(source.data);
    matcher_.reset();
}

data
parser_base::parse_from_source(const cms::source& source)
{
    data data;

    if (pi_.source_events) {

    }

    if (pi_.ast_events || pi_.pickle_events) {
        reset(source);

        data.document = parse(source);

        if (pi_.ast_events) {

        }

        if (pi_.pickle_events) {
            gherkin::pickle_compiler c;

            data.pickles = c.compile(data.document, source.uri);
        }
    }

    return data;
}

const cms::gherkin_document&
parser_base::get_result() const
{ return builder_.get_result(); }

}
