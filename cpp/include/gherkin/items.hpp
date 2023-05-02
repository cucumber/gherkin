#pragma once

#include <vector>

namespace gherkin {

struct item
{
    std::string column;
    std::string text;
};

using items = std::vector<item>;

}
