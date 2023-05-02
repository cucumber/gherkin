#pragma once

#include <string_view>

namespace gherkin {

std::string_view
lstrip(std::string_view in);

std::string_view
rstrip(std::string_view in);

std::string_view
strip(std::string_view in);

}
