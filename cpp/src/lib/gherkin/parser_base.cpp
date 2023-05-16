#include <gherkin/utils.hpp>

#include <gherkin/parser_base.hpp>

namespace gherkin {

parser_base::parser_base(const parser_info& pi)
: pi_(pi)
{}

parser_base::~parser_base()
{}

void
parser_base::parse(const std::string& data)
{ parse_from_source({ .data = data }); }

void
parser_base::parse(const gherkin::file& file)
{
    parse_from_source({
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

void
parser_base::parse_from_source(const cms::source& source)
{
    if (pi_.source_events) {

    }

    if (pi_.ast_events || pi_.pickle_events) {
        reset(source);

        const auto& ast_msg = parse(source);

        if (pi_.ast_events) {

        }

        if (pi_.pickle_events) {
            // pickles compiler
        }
    }

}

const cms::gherkin_document&
parser_base::get_result() const
{ return builder_.get_result(); }

}
