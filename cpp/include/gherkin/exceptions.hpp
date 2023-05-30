#pragma once

#include <stdexcept>
#include <memory>

#include <gherkin/types.hpp>
#include <gherkin/token.hpp>
#include <gherkin/location.hpp>

namespace gherkin {

class parser_error : public std::runtime_error
{
public:
    parser_error(const std::string& message, location location);
    virtual ~parser_error();

    std::string make_message(
        const std::string& message,
        location location
    ) const;

private:
    location location_;
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
    no_such_language_error(const std::string& language, location location);
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

private:
    parser_error_ptrs ptrs_;
};

}
