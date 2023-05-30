#pragma once

#include <ostream>

namespace gherkin {

struct location
{
    std::size_t line;
    std::size_t column;

    std::string to_string() const;
};

inline
std::ostream&
operator<<(std::ostream& os, const location& l)
{
    os << l.to_string();

    return os;
}

}
