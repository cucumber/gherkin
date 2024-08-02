#include <cucumber/gherkin/token.hpp>

namespace cucumber::gherkin {

bool
token::is_eof() const
{ return eof; }

void
token::detach()
{}

std::string_view
token::value() const
{ return is_eof() ? "EOF" : line.get_line_text(); }

}
