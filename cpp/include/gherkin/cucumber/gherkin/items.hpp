#ifndef CUCUMBER_GHERKIN_ITEMS_HPP
#define CUCUMBER_GHERKIN_ITEMS_HPP

#include <cstddef>
#include <string>
#include <vector>

namespace cucumber::gherkin
{

    struct item
    {
        std::size_t column;
        std::string text;
    };

    using items = std::vector<item>;

}

#endif
