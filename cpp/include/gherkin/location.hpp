#pragma once

#include <ostream>

#include <nlohmann/json.hpp>

namespace gherkin {

using json = nlohmann::json;

struct location
{
    std::size_t line;
    std::size_t column;

    std::string to_string() const;

    json to_json() const;
};

inline
std::ostream&
operator<<(std::ostream& os, const location& l)
{
    os << l.to_string();

    return os;
}

}
