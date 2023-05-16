#include <gherkin/utils.hpp>

#include <gherkin/parser_base.hpp>

namespace gherkin {

parser_base::parser_base(const parser_info& pi)
: pi_(pi)
{}

parser_base::~parser_base()
{}

const cms::gherkin_document&
parser_base::parse(const std::string& data)
{
    cms::source s{ .data = data };

    reset(s);

    return parse(s);
}

const cms::gherkin_document&
parser_base::parse(const gherkin::file& file)
{
    cms::source s{
        .uri = file.path,
        .data = slurp(file.path)
    };

    reset(s);

    return parse(s);
}

void
parser_base::reset(const cms::source& source)
{
    builder_.reset(source.uri);
    scanner_.reset(source.data);
    matcher_.reset();
}

const cms::gherkin_document&
parser_base::get_result() const
{ return builder_.get_result(); }

}
