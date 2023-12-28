#include <sstream>

#include <cucumber/gherkin/exceptions.hpp>
#include <cucumber/gherkin/utils.hpp>
#include <cucumber/gherkin/join_utils.hpp>

namespace cucumber::gherkin {

///////////////////////////////////////////////////////////////////////////////
//
// parser error
//
///////////////////////////////////////////////////////////////////////////////
parser_error::parser_error(
    const std::string& message,
    const cms::location& location
)
: std::runtime_error(make_message(message, location)),
location_(location)
{}

parser_error::parser_error(const parser_error& other)
: std::runtime_error(other.what()),
location_(other.location_)
{}

parser_error::~parser_error()
{}

std::string
parser_error::make_message(
    const std::string& message,
    const cms::location& location
) const
{
    std::ostringstream oss;

    oss
        << "(" << location.line << ":" << location.column.value_or(0) << ")"
        << ": " << message;

    return oss.str();
}

bool
parser_error::same_message(const parser_error& other) const
{ return std::strcmp(what(), other.what()) == 0; }

const cms::location&
parser_error::location() const
{ return location_; }

///////////////////////////////////////////////////////////////////////////////
//
// no such language error
//
///////////////////////////////////////////////////////////////////////////////
no_such_language_error::no_such_language_error(
    const std::string& language,
    const cms::location& location
)
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
    make_location(received_token)
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

cms::location
unexpected_token::make_location(const token& t) const
{
    return
        t.location.column.value_or(0) > 1
        ? t.location
        : cms::location{
            .line = t.location.line,
            .column = t.line.indent() + 1
        }
        ;
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

const parser_error_ptrs&
composite_parser_error::errors() const
{ return ptrs_; }

}
