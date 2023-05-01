#include <gherkin/token.hpp>

namespace gherkin {

bool
token::is_eof() const
{ return line.text.empty(); }

void
token::detach()
{}

std::string_view
token::value() const
{ return line.text; }

}
