#pragma once

#include <string_view>
#include <memory>

#include <cucumber/gherkin/file.hpp>
#include <cucumber/gherkin/token.hpp>
#include <cucumber/gherkin/line.hpp>

namespace cucumber::gherkin {

struct next_line_result
{
    bool eof = true;
    std::string text;
};

class token_scanner
{
public:
    token_scanner();
    token_scanner(std::string_view data);
    token_scanner(const file& file);

    virtual ~token_scanner();

    void reset();
    void reset(std::string_view data);
    void reset(const file& file);

    token read();

private:
    next_line_result next_line();

    std::istream& input();

    using input_ptr = std::unique_ptr<std::istream>;

    std::size_t line_ = 0;
    input_ptr ip_;
};

using token_scanner_ptr = std::unique_ptr<token_scanner>;

template <typename... Args>
token_scanner_ptr
new_token_scanner(Args&&... args)
{ return std::make_unique<token_scanner>(std::forward<Args>(args)...); }

}
