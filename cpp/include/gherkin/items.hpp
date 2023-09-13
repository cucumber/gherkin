#pragma once

#include <vector>

namespace gherkin {

struct item
{
    std::size_t column;
    std::string text;
};

using items = std::vector<item>;

}
