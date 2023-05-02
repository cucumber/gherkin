#include <gherkin/token.hpp>

namespace gherkin {

bool
token::is_eof() const
{ return line.is_empty(); }

void
token::detach()
{}

std::string_view
token::value() const
{ return is_eof() ? "EOF" : line.get_line_text(); }

}
