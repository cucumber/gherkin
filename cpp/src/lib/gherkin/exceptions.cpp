#include <sstream>

#include <gherkin/exceptions.hpp>
#include <gherkin/utils.hpp>
#include <gherkin/join_utils.hpp>

namespace gherkin {

///////////////////////////////////////////////////////////////////////////////
//
// parser error
//
///////////////////////////////////////////////////////////////////////////////
parser_error::parser_error(const std::string& message, location location)
: std::runtime_error(make_message(message, location))
{}

parser_error::~parser_error()
{}

std::string
parser_error::make_message(
    const std::string& message,
    location location
) const
{
    std::ostringstream oss;

    oss << location << ": " << message;

    return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
//
// no such language error
//
///////////////////////////////////////////////////////////////////////////////
no_such_language_error::no_such_language_error(
    const std::string& language,
    location location)
: parser_error("Language not supported: " + language, location)
{}

no_such_language_error::~no_such_language_error()
{}

///////////////////////////////////////////////////////////////////////////////
//
// unexpected token
//
///////////////////////////////////////////////////////////////////////////////
unexpected_token::unexpected_token(
    const token& received_token,
    const std::string& expected_tokens,
    const std::string& state_comment
)
: parser_error(
    make_message(received_token, expected_tokens),
    received_token.location
),
received_token_(received_token),
expected_tokens_(expected_tokens),
state_comment_(state_comment)
{}

unexpected_token::~unexpected_token()
{}

std::string
unexpected_token::make_message(
    const token& received_token,
    const std::string& expected_tokens
) const
{
    std::ostringstream oss;

    oss
        << "expected: " << expected_tokens
        << ", got '" << strip(received_token.value()) << "'"
        ;

    return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
//
// unexpected eof
//
///////////////////////////////////////////////////////////////////////////////
unexpected_eof::unexpected_eof(
    const token& received_token,
    const std::string& expected_tokens,
    const std::string& state_comment
)
: parser_error(
    make_message(expected_tokens),
    received_token.location
),
expected_tokens_(expected_tokens),
state_comment_(state_comment)
{}

unexpected_eof::~unexpected_eof()
{}

std::string
unexpected_eof::make_message(const std::string& expected_tokens) const
{
    std::ostringstream oss;

    oss << "unexpected end of file, expected: " << expected_tokens;

    return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
//
// composite parser error
//
///////////////////////////////////////////////////////////////////////////////
composite_parser_error::composite_parser_error(const parser_error_ptrs& ptrs)
: parser_error("", {}),
ptrs_(ptrs)
{}

composite_parser_error::~composite_parser_error()
{}

std::string
composite_parser_error::make_message(const parser_error_ptrs& ptrs) const
{
    strings errs;

    for (const auto& p : ptrs) {
        errs.push_back(p->what());
    }

    std::ostringstream oss;

    oss << "Parser errors:\n" << join("\n", errs);

    return oss.str();
}

}
