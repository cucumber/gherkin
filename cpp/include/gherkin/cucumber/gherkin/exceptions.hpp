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

    namespace cms = cucumber::messages;

    class ParserError : public std::runtime_error
    {
    public:
        ParserError(const std::string& message, const cms::Location& location);

        ParserError(const ParserError& other);
        ParserError& operator=(const ParserError&) = default;
        ParserError(ParserError&&) = default;
        ParserError& operator=(ParserError&&) = default;

        ~ParserError() override;

        static std::string MakeMessage(const std::string& message, const cms::Location& location);

        [[nodiscard]] bool SameMessage(const ParserError& other) const;

        [[nodiscard]] const cms::Location& Location() const;

    private:
        cms::Location location;
    };

    using parser_error_ptr = std::shared_ptr<ParserError>;
    using parser_error_ptrs = std::vector<parser_error_ptr>;

    template<typename Error, typename... Args>
    parser_error_ptr NewParserError(Args&&... args)
    {
        return std::make_shared<Error>(std::forward<Args>(args)...);
    }

    using ast_builder_error = ParserError;

    class NoSuchLanguageError : public ParserError
    {
    public:
        NoSuchLanguageError(const std::string& language, const cms::Location& location);

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

        static cms::Location MakeLocation(const Token& receivedToken);

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
        CompositeParserError(parser_error_ptrs ptrs);

        ~CompositeParserError() override;
        CompositeParserError(const CompositeParserError&) = default;
        CompositeParserError& operator=(const CompositeParserError&) = default;
        CompositeParserError(CompositeParserError&&) = default;
        CompositeParserError& operator=(CompositeParserError&&) = default;

        static std::string MakeMessage(const parser_error_ptrs& ptrs);

        [[nodiscard]] const parser_error_ptrs& Errors() const;

    private:
        parser_error_ptrs ptrs;
    };

}

#endif
