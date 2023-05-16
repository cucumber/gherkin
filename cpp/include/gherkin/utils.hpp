#pragma once

#include <string>
#include <string_view>

namespace gherkin {

std::string_view
lstrip(std::string_view in, std::string_view chars = " ");

std::string_view
rstrip(std::string_view in, std::string_view chars = " ");

std::string_view
strip(std::string_view in, std::string_view chars = " ");

void
replace(std::string& s, std::string_view what, std::string_view with);

std::string
replace(const std::string& s, std::string_view what, std::string_view with);

std::string
slurp(const std::string& path);

template <typename C>
struct reverse
{
    reverse(C& c)
    : c_(c)
    {}

    auto begin()
    { return c_.rbegin(); }

    auto end()
    { return c_.rend(); }

    C& c_;
};

}
