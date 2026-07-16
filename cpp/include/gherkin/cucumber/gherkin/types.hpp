#pragma once

#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace cucumber::gherkin
{

    using strings = std::vector<std::string>;
    using strings_map = std::unordered_map<std::string, strings>;
    using string_set = std::set<std::string>;
    using string_set_map = std::unordered_map<std::string, string_set>;
    using string_map = std::unordered_map<std::string, std::string>;

    using string_views = std::vector<std::string_view>;
    using string_view_set = std::set<std::string_view>;

}
