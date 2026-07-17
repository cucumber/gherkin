#ifndef CUCUMBER_GHERKIN_PARSE_ERROR_HPP
#define CUCUMBER_GHERKIN_PARSE_ERROR_HPP

#include "cucumber/messages/Location.hpp"
#include <nlohmann/json_fwd.hpp>
#include <string>

namespace cucumber::gherkin
{
    struct ParseError
    {
        std::string uri;
        messages::Location location;
        std::string message;

        [[nodiscard]] nlohmann::json to_json() const;
    };

}

#endif
