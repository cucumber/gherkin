#include "cucumber/gherkin/token.hpp"
#include <string_view>

namespace cucumber::gherkin
{
    bool Token::IsEof() const
    {
        return eof;
    }

    std::string_view Token::Value() const
    {
        return IsEof() ? "EOF" : line.GetLineText();
    }
}
