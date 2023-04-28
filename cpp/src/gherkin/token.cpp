#include <gherkin/token.hpp>

namespace gherkin {

bool
token::is_eof() const
{ return line.empty(); }

std::string_view
token::value() const
{ return line.text(); }

}
