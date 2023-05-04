#pragma once

#include <vector>

namespace gherkin {

struct item
{
    std::size_t column = 0;
    std::string text;
};

using items = std::vector<item>;

}
