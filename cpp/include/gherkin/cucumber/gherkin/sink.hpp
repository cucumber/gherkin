#pragma once

#include <functional>
#include <nlohmann/json.hpp>

namespace cucumber::gherkin {

using json = nlohmann::json;

using sink_cb = std::function<void (const json&)>;

}
