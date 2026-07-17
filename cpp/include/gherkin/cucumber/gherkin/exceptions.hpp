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

        virtual ~ParserError();

        std::string make_message(const std::string& message, const cms::Location& location) const;

        bool same_message(const ParserError& other) const;

        const cms::Location& location() const;

    private:
        cms::Location location_;
    };

    using parser_error_ptr = std::shared_ptr<ParserError>;
    using parser_error_ptrs = std::vector<parser_error_ptr>;

    template<typename Error, typename... Args>
    parser_error_ptr new_parser_error(Args&&... args)
    {
        return std::make_shared<Error>(std::forward<Args>(args)...);
    }

    using ast_builder_error = ParserError;

    class NoSuchLanguageError : public ParserError
    {
    public:
        NoSuchLanguageError(const std::string& language, const cms::Location& location);

        virtual ~NoSuchLanguageError();
    };

    class UnexpectedToken : public ParserError
    {
    public:
        UnexpectedToken(const Token& received_token, const std::string& expected_tokens, const std::string& state_comment);

        virtual ~UnexpectedToken();

        std::string make_message(const Token& received_token, const std::string& expected_tokens) const;

        cms::Location make_location(const Token& received_token) const;

    private:
        Token received_token_;
        std::string expected_tokens_;
        std::string state_comment_;
    };

    class UnexpectedEof : public ParserError
    {
    public:
        UnexpectedEof(const Token& received_token, const std::string& expected_tokens, const std::string& state_comment);

        virtual ~UnexpectedEof();

        std::string make_message(const std::string& expected_tokens) const;

    private:
        std::string expected_tokens_;
        std::string state_comment_;
    };

    class CompositeParserError : public ParserError
    {
    public:
        CompositeParserError(const parser_error_ptrs& ptrs);

        virtual ~CompositeParserError();

        std::string make_message(const parser_error_ptrs& ptrs) const;

        const parser_error_ptrs& errors() const;

    private:
        parser_error_ptrs ptrs_;
    };

}

#endif
