#pragma once

#include <string>
#include <functional>

namespace gherkin {

using id_generator_func = std::function<std::string ()>;

struct parser_info
{
    std::string language = "en";
    bool include_source = true;
    bool include_ast = true;
    bool include_pickles = true;
    id_generator_func id_generator;
};

}
