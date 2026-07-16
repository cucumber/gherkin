#include "cucumber/gherkin/parse_error.hpp"

namespace cucumber::gherkin
{

    json ParseError::to_json() const
    {
        json doc;

        doc["parseError"]["source"]["uri"] = uri;
        location.to_json(doc["parseError"]["source"]["location"]);
        doc["parseError"]["message"] = message;

        return doc;
    }

}
