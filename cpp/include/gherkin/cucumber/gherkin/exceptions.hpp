#ifndef CUCUMBER_GHERKIN_EXCEPTIONS_HPP
#define CUCUMBER_GHERKIN_EXCEPTIONS_HPP

#include "cucumber/gherkin/token.hpp"
#include "cucumber/messages/Location.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace cucumber::gherkin
{
    class ParserError : public std::runtime_error
    {
    public:
        ParserError(const std::string& message, const messages::Location& location);

        ParserError(const ParserError& other);
        ParserError& operator=(const ParserError&) = default;
        ParserError(ParserError&&) = default;
        ParserError& operator=(ParserError&&) = default;

        ~ParserError() override;

        static std::string MakeMessage(const std::string& message, const messages::Location& location);

        [[nodiscard]] bool SameMessage(const ParserError& other) const;

        [[nodiscard]] const messages::Location& Location() const;

    private:
        messages::Location location;
    };

    using ParserErrorPtr = std::shared_ptr<ParserError>;
    using ParserErrorPtrs = std::vector<ParserErrorPtr>;

    template<typename Error, typename... Args>
    ParserErrorPtr NewParserError(Args&&... args)
    {
        return std::make_shared<Error>(std::forward<Args>(args)...);
    }

    using AstBuilderError = ParserError;

    class NoSuchLanguageError : public ParserError
    {
    public:
        NoSuchLanguageError(const std::string& language, const messages::Location& location);

        ~NoSuchLanguageError() override;
        NoSuchLanguageError(const NoSuchLanguageError&) = default;
        NoSuchLanguageError& operator=(const NoSuchLanguageError&) = default;
        NoSuchLanguageError(NoSuchLanguageError&&) = default;
        NoSuchLanguageError& operator=(NoSuchLanguageError&&) = default;
    };

    class UnexpectedToken : public ParserError
    {
    public:
        UnexpectedToken(const Token& receivedToken, const std::string& expectedTokens, std::string stateComment);

        ~UnexpectedToken() override;
        UnexpectedToken(const UnexpectedToken&) = default;
        UnexpectedToken& operator=(const UnexpectedToken&) = default;
        UnexpectedToken(UnexpectedToken&&) = default;
        UnexpectedToken& operator=(UnexpectedToken&&) = default;

        static std::string MakeMessage(const Token& receivedToken, const std::string& expectedTokens);

        static messages::Location MakeLocation(const Token& receivedToken);

    private:
        Token receivedToken;
        std::string expectedTokens;
        std::string stateComment;
    };

    class UnexpectedEof : public ParserError
    {
    public:
        UnexpectedEof(const Token& receivedToken, const std::string& expectedTokens, std::string stateComment);

        ~UnexpectedEof() override;
        UnexpectedEof(const UnexpectedEof&) = default;
        UnexpectedEof& operator=(const UnexpectedEof&) = default;
        UnexpectedEof(UnexpectedEof&&) = default;
        UnexpectedEof& operator=(UnexpectedEof&&) = default;

        static std::string MakeMessage(const std::string& expectedTokens);

    private:
        std::string expectedTokens;
        std::string stateComment;
    };

    class CompositeParserError : public ParserError
    {
    public:
        CompositeParserError(ParserErrorPtrs ptrs);

        ~CompositeParserError() override;
        CompositeParserError(const CompositeParserError&) = default;
        CompositeParserError& operator=(const CompositeParserError&) = default;
        CompositeParserError(CompositeParserError&&) = default;
        CompositeParserError& operator=(CompositeParserError&&) = default;

        static std::string MakeMessage(const ParserErrorPtrs& ptrs);

        [[nodiscard]] const ParserErrorPtrs& Errors() const;

    private:
        ParserErrorPtrs ptrs;
    };

}

#endif
