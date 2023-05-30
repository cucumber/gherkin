#pragma once

#include <string>

#include <gherkin/location.hpp>

#include <nlohmann/json.hpp>

namespace gherkin {

using json = nlohmann::json;

struct parse_error
{
    std::string uri;
    gherkin::location location;
    std::string message;

    json to_json() const;
};

}
