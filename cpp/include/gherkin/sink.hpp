#pragma once

#include <functional>
#include <nlohmann/json.hpp>

namespace gherkin {

using json = nlohmann::json;

using sink_cb = std::function<void (const json&)>;

}
