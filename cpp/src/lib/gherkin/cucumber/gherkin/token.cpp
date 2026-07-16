#include "cucumber/gherkin/token.hpp"
#include <string_view>

namespace cucumber::gherkin
{

    bool token::is_eof() const
    {
        return eof;
    }

    std::string_view token::value() const
    {
        return is_eof() ? "EOF" : line.get_line_text();
    }

}
