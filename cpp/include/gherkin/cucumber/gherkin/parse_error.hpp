#pragma once

#include <string>

#include <nlohmann/json.hpp>

#include <cucumber/messages/location.hpp>

namespace cucumber::gherkin {

using json = nlohmann::json;
namespace cms = cucumber::messages;

struct parse_error
{
    std::string uri;
    cms::location location;
    std::string message;

    json to_json() const;
};

}
