#include "cucumber/gherkin/ParseError.hpp"
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

namespace cucumber::gherkin
{
    nlohmann::json ParseError::to_json() const
    {
        nlohmann::json doc;

        doc["parseError"]["source"]["uri"] = uri;
        location.to_json(doc["parseError"]["source"]["location"]);
        doc["parseError"]["message"] = message;

        return doc;
    }

}
