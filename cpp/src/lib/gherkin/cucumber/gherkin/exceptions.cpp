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
#include <utility>

namespace cucumber::gherkin
{

    ///////////////////////////////////////////////////////////////////////////////
    //
    // Parser error
    //
    ///////////////////////////////////////////////////////////////////////////////
    ParserError::ParserError(const std::string& message, const messages::Location& location)
        : std::runtime_error(MakeMessage(message, location))
        , location(location)
    {}

    ParserError::ParserError(const ParserError& other)
        : std::runtime_error(other.what())
        , location(other.location)
    {}

    std::string ParserError::MakeMessage(const std::string& message, const messages::Location& location)
    {
        std::ostringstream stream;

        stream << "(" << location.line << ":" << location.column.value_or(0) << ")"
               << ": " << message;

        return stream.str();
    }

    bool ParserError::SameMessage(const ParserError& other) const
    {
        return std::strcmp(what(), other.what()) == 0;
    }

    const messages::Location& ParserError::Location() const
    {
        return location;
    }

    ///////////////////////////////////////////////////////////////////////////////
    //
    // no such language error
    //
    ///////////////////////////////////////////////////////////////////////////////
    NoSuchLanguageError::NoSuchLanguageError(const std::string& language, const messages::Location& location)
        : ParserError("Language not supported: " + language, location)
    {}

    ///////////////////////////////////////////////////////////////////////////////
    //
    // unexpected Token
    //
    ///////////////////////////////////////////////////////////////////////////////
    UnexpectedToken::UnexpectedToken(const Token& receivedToken, const std::string& expectedTokens, std::string stateComment) // NOLINT(bugprone-easily-swappable-parameters)
        : ParserError(MakeMessage(receivedToken, expectedTokens), MakeLocation(receivedToken))
        , receivedToken(receivedToken)
        , expectedTokens(expectedTokens)
        , stateComment(std::move(stateComment))
    {}

    std::string UnexpectedToken::MakeMessage(const Token& receivedToken, const std::string& expectedTokens)
    {
        std::ostringstream stream;

        stream << "expected: " << expectedTokens << ", got '" << Strip(receivedToken.Value()) << "'";

        return stream.str();
    }

    messages::Location UnexpectedToken::MakeLocation(const Token& receivedToken)
    {
        return receivedToken.location.column.value_or(0) > 1 ? receivedToken.location : messages::Location{ receivedToken.location.line, receivedToken.line.Indent() + 1 };
    }

    ///////////////////////////////////////////////////////////////////////////////
    //
    // unexpected eof
    //
    ///////////////////////////////////////////////////////////////////////////////
    UnexpectedEof::UnexpectedEof(const Token& receivedToken, const std::string& expectedTokens, std::string stateComment) // NOLINT(bugprone-easily-swappable-parameters)
        : ParserError(MakeMessage(expectedTokens), receivedToken.location)
        , expectedTokens(expectedTokens)
        , stateComment(std::move(stateComment))
    {}

    std::string UnexpectedEof::MakeMessage(const std::string& expectedTokens)
    {
        std::ostringstream stream;

        stream << "unexpected end of file, expected: " << expectedTokens;

        return stream.str();
    }

    ///////////////////////////////////////////////////////////////////////////////
    //
    // composite Parser error
    //
    ///////////////////////////////////////////////////////////////////////////////
    CompositeParserError::CompositeParserError(ParserErrorPtrs ptrs)
        : ParserError("", {})
        , ptrs(std::move(ptrs))
    {}

    std::string CompositeParserError::MakeMessage(const ParserErrorPtrs& ptrs)
    {
        Strings errs;

        for (const auto& errorPointer : ptrs)
        {
            errs.emplace_back(errorPointer->what());
        }

        std::ostringstream stream;

        stream << "Parser errors:\n" << Join("\n", errs);

        return stream.str();
    }

    const ParserErrorPtrs& CompositeParserError::Errors() const
    {
        return ptrs;
    }

}
