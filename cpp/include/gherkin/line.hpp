#pragma once

#include <cstddef>
#include <string>

namespace gherkin {

struct line
{
    std::string text;
    std::size_t number;
    std::size_t indent;
    std::string trimmed_text;
};

}
