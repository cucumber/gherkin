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

json
location::to_json() const
{
    json j;

    j["line"] = line;
    j["column"] = column;

    return j;
}

}
