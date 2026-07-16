#include "cucumber/gherkin/exceptions.hpp"
#include "cucumber/gherkin/join_utils.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/types.hpp"
#include "cucumber/gherkin/utils.hpp"
#include "cucumber/messages/Location.hpp"
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <string>

namespace cucumber::gherkin
{

    ///////////////////////////////////////////////////////////////////////////////
    //
    // Parser error
    //
    ///////////////////////////////////////////////////////////////////////////////
    ParserError::ParserError(const std::string& message, const cms::Location& location)
        : std::runtime_error(make_message(message, location))
        , location_(location)
    {}

    ParserError::ParserError(const ParserError& other)
        : std::runtime_error(other.what())
        , location_(other.location_)
    {}

    ParserError::~ParserError()
    {}

    std::string ParserError::make_message(const std::string& message, const cms::Location& location) const
    {
        std::ostringstream stream;

        stream << "(" << location.line << ":" << location.column.value_or(0) << ")"
               << ": " << message;

        return stream.str();
    }

    bool ParserError::same_message(const ParserError& other) const
    {
        return std::strcmp(what(), other.what()) == 0;
    }

    const cms::Location& ParserError::location() const
    {
        return location_;
    }

    ///////////////////////////////////////////////////////////////////////////////
    //
    // no such language error
    //
    ///////////////////////////////////////////////////////////////////////////////
    NoSuchLanguageError::NoSuchLanguageError(const std::string& language, const cms::Location& location)
        : ParserError("Language not supported: " + language, location)
    {}

    NoSuchLanguageError::~NoSuchLanguageError()
    {}

    ///////////////////////////////////////////////////////////////////////////////
    //
    // unexpected Token
    //
    ///////////////////////////////////////////////////////////////////////////////
    UnexpectedToken::UnexpectedToken(const Token& received_token, const std::string& expected_tokens, const std::string& state_comment)
        : ParserError(make_message(received_token, expected_tokens), make_location(received_token))
        , received_token_(received_token)
        , expected_tokens_(expected_tokens)
        , state_comment_(state_comment)
    {}

    UnexpectedToken::~UnexpectedToken()
    {}

    std::string UnexpectedToken::make_message(const Token& received_token, const std::string& expected_tokens) const
    {
        std::ostringstream stream;

        stream << "expected: " << expected_tokens << ", got '" << strip(received_token.value()) << "'";

        return stream.str();
    }

    cms::Location UnexpectedToken::make_location(const Token& received_token) const
    {
        return received_token.location.column.value_or(0) > 1 ? received_token.location : cms::Location{ received_token.location.line, received_token.line.indent() + 1 };
    }

    ///////////////////////////////////////////////////////////////////////////////
    //
    // unexpected eof
    //
    ///////////////////////////////////////////////////////////////////////////////
    UnexpectedEof::UnexpectedEof(const Token& received_token, const std::string& expected_tokens, const std::string& state_comment)
        : ParserError(make_message(expected_tokens), received_token.location)
        , expected_tokens_(expected_tokens)
        , state_comment_(state_comment)
    {}

    UnexpectedEof::~UnexpectedEof()
    {}

    std::string UnexpectedEof::make_message(const std::string& expected_tokens) const
    {
        std::ostringstream stream;

        stream << "unexpected end of file, expected: " << expected_tokens;

        return stream.str();
    }

    ///////////////////////////////////////////////////////////////////////////////
    //
    // composite Parser error
    //
    ///////////////////////////////////////////////////////////////////////////////
    CompositeParserError::CompositeParserError(const parser_error_ptrs& ptrs)
        : ParserError("", {})
        , ptrs_(ptrs)
    {}

    CompositeParserError::~CompositeParserError()
    {}

    std::string CompositeParserError::make_message(const parser_error_ptrs& ptrs) const
    {
        strings errs;

        for (const auto& error_pointer : ptrs)
        {
            errs.push_back(error_pointer->what());
        }

        std::ostringstream stream;

        stream << "Parser errors:\n" << join("\n", errs);

        return stream.str();
    }

    const parser_error_ptrs& CompositeParserError::errors() const
    {
        return ptrs_;
    }

}
