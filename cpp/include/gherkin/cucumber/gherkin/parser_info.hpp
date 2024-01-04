#pragma once

#include <string>
#include <functional>

namespace cucumber::gherkin {

using id_generator_func = std::function<std::string ()>;

struct parser_info
{
    std::string language = "en";
    id_generator_func id_generator;
};

}
