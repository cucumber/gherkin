#pragma once

#include <string>
#include <functional>
#include <nlohmann/json.hpp>

namespace gherkin {

using id_generator_func = std::function<std::string ()>;

using json = nlohmann::json;

using json_cb = std::function<void (const json&)>;

struct parser_info
{
    std::string language = "en";
    bool include_source = true;
    bool include_ast = true;
    bool include_pickles = true;
    id_generator_func id_generator;
    json_cb sink;
};

}
