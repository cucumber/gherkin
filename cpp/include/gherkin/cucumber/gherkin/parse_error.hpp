#pragma once

#include "cucumber/messages/Location.hpp"
#include <nlohmann/json.hpp>
#include <string>

namespace cucumber::gherkin
{

    using json = nlohmann::json;
    namespace cms = cucumber::messages;

    struct parse_error
    {
        std::string uri;
        cms::Location location;
        std::string message;

        json to_json() const;
    };

}
