#pragma once

#include <string>
#include <memory>

#include <gherkin/file.hpp>
#include <gherkin/token.hpp>
#include <gherkin/line.hpp>

namespace gherkin {

struct next_line_result
{
    bool has_line = false;
    std::string text;
};

class token_scanner
{
public:
    token_scanner();
    token_scanner(const std::string& text);
    token_scanner(const file& file);

    virtual ~token_scanner();

    void reset(const std::string& text);
    void reset(const file& file);

    token_scanner(const file& file);

    token read();

private:
    void reset();

    next_line_result next_line();

    std::istream& input();

    using input_ptr = std::unique_ptr<std::istream>;

    std::size_t line_ = 0;
    input_ptr ip_;
};

}
