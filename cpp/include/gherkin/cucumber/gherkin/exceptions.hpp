#pragma once

#include <stdexcept>
#include <memory>

#include <cucumber/messages/location.hpp>

#include <cucumber/gherkin/types.hpp>
#include <cucumber/gherkin/token.hpp>

namespace cucumber::gherkin {

namespace cms = cucumber::messages;

class parser_error : public std::runtime_error
{
public:
    parser_error(
        const std::string& message,
        const cms::location& location
    );

    parser_error(const parser_error& other);

    virtual ~parser_error();

    std::string make_message(
        const std::string& message,
        const cms::location& location
    ) const;

    bool same_message(const parser_error& other) const;

    const cms::location& location() const;

private:
    cms::location location_;
};

using parser_error_ptr = std::shared_ptr<parser_error>;
using parser_error_ptrs = std::vector<parser_error_ptr>;

template <typename Error, typename... Args>
parser_error_ptr
new_parser_error(Args&&... args)
{ return std::make_shared<Error>(std::forward<Args>(args)...); }

using ast_builder_error = parser_error;

class no_such_language_error : public parser_error
{
public:
    no_such_language_error(
        const std::string& language,
        const cms::location& location
    );

    virtual ~no_such_language_error();
};

class unexpected_token : public parser_error
{
public:
    unexpected_token(
        const token& received_token,
        const std::string& expected_tokens,
        const std::string& state_comment
    );

    virtual ~unexpected_token();

    std::string make_message(
        const token& received_token,
        const std::string& expected_tokens
    ) const;

    cms::location make_location(const token& t) const;

private:
    token received_token_;
    std::string expected_tokens_;
    std::string state_comment_;
};

class unexpected_eof : public parser_error
{
public:
    unexpected_eof(
        const token& received_token,
        const std::string& expected_tokens,
        const std::string& state_comment
    );

    virtual ~unexpected_eof();

    std::string make_message(const std::string& expected_tokens) const;

private:
    std::string expected_tokens_;
    std::string state_comment_;
};

class composite_parser_error : public parser_error
{
public:
    composite_parser_error(const parser_error_ptrs& ptrs);

    virtual ~composite_parser_error();

    std::string make_message(const parser_error_ptrs& ptrs) const;

    const parser_error_ptrs& errors() const;

private:
    parser_error_ptrs ptrs_;
};

}
