#include <gherkin/utils.hpp>

namespace gherkin {

std::string_view
lstrip(std::string_view in)
{
    auto it = in.begin();
    auto end = in.end();

    while (it != end && *it != ' ')
        ++it;

    return {it, end};
}

std::string_view
rstrip(std::string_view in)
{
    auto it = in.rbegin();
    auto end = in.rend();

    while (it != end && *it != ' ')
        ++it;

    return {end.base(), it.base()};
}

std::string_view
strip(std::string_view in)
{ return lstrip(rstrip(in)); }

}
