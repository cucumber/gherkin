#pragma once

#include <string>
#include <string_view>
#include <regex>

namespace gherkin {

std::string
slurp(const std::string& path);

namespace detail {

template <typename CharT>
auto
strip(auto it, auto end, std::basic_string_view<CharT> chars)
{
    while (it != end) {
        std::size_t count = 0;

        for (auto c: chars) {
            count += *it == c;
        }

        if (count == 0) {
            break;
        }

        ++it;
    }

    return it;
}

} // namespace detail

template <typename CharT>
std::basic_string_view<CharT>
lstrip(
    std::basic_string_view<CharT> in,
    std::basic_string_view<CharT> chars = " "
)
{
    auto it = in.begin();
    auto end = in.end();

    it = detail::strip(it, end, chars);

    return {it, end};
}

template <typename CharT>
std::basic_string_view<CharT>
lstrip(
    const std::basic_string<CharT>& in,
    std::basic_string_view<CharT> chars = " "
)
{ return lstrip(std::basic_string_view<CharT>{in.data(), in.size()}, chars); }

template <typename CharT>
std::basic_string_view<CharT>
rstrip(
    std::basic_string_view<CharT> in,
    std::basic_string_view<CharT> chars = " "
)
{
    auto it = in.rbegin();
    auto end = in.rend();

    it = detail::strip(it, end, chars);

    return {end.base(), it.base()};
}

template <typename CharT>
std::basic_string_view<CharT>
rstrip(
    const std::basic_string<CharT>& in,
    std::basic_string_view<CharT> chars = " "
)
{ return rstrip(std::basic_string_view<CharT>{in.data(), in.size()}, chars); }

template <typename CharT>
std::basic_string_view<CharT>
strip(
    std::basic_string_view<CharT> in,
    std::basic_string_view<CharT> chars = " "
)
{ return lstrip(rstrip(in, chars), chars); }

template <typename CharT>
std::basic_string_view<CharT>
strip(
    const std::basic_string<CharT>& in,
    std::basic_string_view<CharT> chars = " "
)
{ return strip(std::basic_string_view<CharT>{in.data(), in.size()}, chars); }

template <typename CharT>
void
replace(
    std::basic_string<CharT>& s,
    std::basic_string_view<CharT> what,
    std::basic_string_view<CharT> with
)
{
    std::string::size_type pos;

    while ((pos = s.find(what)) != std::basic_string<CharT>::npos) {
        s.replace(pos, what.size(), with);
    }
}

template <typename CharT>
std::basic_string<CharT>
replace(
    const std::basic_string<CharT>& s,
    std::basic_string_view<CharT> what,
    std::basic_string_view<CharT> with
)
{
    std::basic_string<CharT> t = s;

    replace(t, what, with);

    return t;
}

template <typename CharT>
std::basic_string<CharT>
replace(
    const std::basic_string<CharT>& s,
    const std::basic_string<CharT>& what,
    const std::basic_string<CharT>& with
)
{ return replace(s, what, with); }

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
