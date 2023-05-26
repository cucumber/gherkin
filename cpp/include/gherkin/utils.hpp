#pragma once

#include <string>
#include <string_view>
#include <regex>

namespace gherkin {

std::string_view
spaces_pattern();

std::string_view
spaces_no_nl_pattern();

std::size_t
codepoint_count(std::string_view s);

std::string
slurp(const std::string& path);

struct strip_pattern
{
    std::string_view prefix;
    std::string_view chars;
    std::string_view suffix;

    std::string str() const;
};

std::string
strip(std::string_view what, const strip_pattern& p);

std::string
lstrip(std::string_view in, std::string_view chars = spaces_pattern());

std::string
rstrip(std::string_view in, std::string_view chars = spaces_pattern());

std::string
strip(std::string_view in, std::string_view chars = spaces_pattern());

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
