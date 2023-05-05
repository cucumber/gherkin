#include <gherkin/utils.hpp>

namespace gherkin {

std::string_view
lstrip(std::string_view in, std::string_view chars)
{
    auto it = in.begin();
    auto end = in.end();

    for (auto c: chars) {
        while (it != end && *it == c) {
            ++it;
        }
    }

    return {it, end};
}

std::string_view
rstrip(std::string_view in, std::string_view chars)
{
    auto it = in.rbegin();
    auto end = in.rend();

    for (auto c: chars) {
        while (it != end && *it == c) {
            ++it;
        }
    }

    return {end.base(), it.base()};
}

std::string_view
strip(std::string_view in, std::string_view chars)
{ return lstrip(rstrip(in, chars), chars); }

void
replace(std::string& s, std::string_view what, std::string_view with)
{
    std::string::size_type pos;

    while ((pos = s.find(what)) != std::string::npos) {
        s.replace(pos, what.size(), with);
    }
}

std::string
replace(const std::string& s, std::string_view what, std::string_view with)
{
    std::string t = s;

    replace(t, what, with);

    return t;
}

}
