#include <cucumber/gherkin/parse_error.hpp>

namespace cucumber::gherkin {

json
parse_error::to_json() const
{
    json j;

    j["parseError"]["source"]["uri"] = uri;
    location.to_json(j["parseError"]["source"]["location"]);
    j["parseError"]["message"] = message;

    return j;
}

}
