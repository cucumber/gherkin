#ifndef CUCUMBER_GHERKIN_SINK_HPP
#define CUCUMBER_GHERKIN_SINK_HPP

#include <functional>
#include <nlohmann/json.hpp>

namespace cucumber::gherkin
{

    using Json = nlohmann::json;

    using SinkCb = std::function<void(const json&)>;

}

#endif
