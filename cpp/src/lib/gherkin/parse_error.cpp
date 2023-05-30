#include <gherkin/parse_error.hpp>

namespace gherkin {

json
parse_error::to_json() const
{
    json j;

    j["parseError"]["source"]["uri"] = uri;
    j["parseError"]["source"]["location"] = location.to_json();
    j["parseError"]["message"] = message;

    return j;
}

}
