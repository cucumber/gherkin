#include <sstream>

#include <gherkin/location.hpp>

namespace gherkin {

std::string
location::to_string() const
{
    std::ostringstream oss;

    oss << "(" << line << ":" << column << ")";

    return oss.str();
}

}
