#ifndef CUCUMBER_GHERKIN_TYPES_HPP
#define CUCUMBER_GHERKIN_TYPES_HPP

#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace cucumber::gherkin
{

    using Strings = std::vector<std::string>;
    using StringsMap = std::unordered_map<std::string, Strings>;
    using StringSet = std::set<std::string>;
    using StringSetMap = std::unordered_map<std::string, StringSet>;
    using StringMap = std::unordered_map<std::string, std::string>;

    using StringViews = std::vector<std::string_view>;
    using StringViewSet = std::set<std::string_view>;

}

#endif
