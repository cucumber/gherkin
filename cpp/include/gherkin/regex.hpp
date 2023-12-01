#pragma once

#include <regex>
#include <charconv>

#include <gherkin/utils.hpp>
#include <gherkin/types.hpp>
#include <gherkin/log.hpp>

namespace gherkin {

struct regex_result
{
    bool match = false;
    string_views matches;
};

void
split(
    const std::string& re,
    const std::string& expr,
    strings& list
);

strings
split(const std::string& re, const std::string& expr);

std::string
subst(const std::string& s, const std::string& re, const std::string& what = {});

void
subst(std::string& s, const std::string& re, const std::string& what = {});

namespace detail {

struct null_arg{};

template <typename CharT, typename SubMatch, typename Arg = null_arg>
auto
extract_submatch(const SubMatch& sm, Arg&& a)
{
    using arg_type = std::decay_t<Arg>;
    using sv_type = std::basic_string_view<CharT>;

    constexpr bool is_string =
        std::is_same_v<arg_type, std::basic_string<CharT>>
        ||
        std::is_same_v<arg_type, std::basic_string_view<CharT>>
        ;

    constexpr bool is_number =
        std::is_integral_v<arg_type>
        ||
        std::is_floating_point_v<arg_type>
        ;

    sv_type sv{sm.first, static_cast<std::size_t>(sm.length())};

    if constexpr (is_string) {
        a.assign(sv);
    } else if constexpr (is_number) {
        auto [p, ec] = std::from_chars(sv.begin(), sv.end(), a);

        die_unless(
            ec == std::errc(),
            "failed to convert \"",
            sv,
            "\" to ",
            declname(a)
        );
    } else if constexpr (!std::is_same_v<arg_type, null_arg>) {
        die("unsupported argument: ", declname(a));
    }

    return sv;
}

template <std::size_t N, typename MatchResult>
void
check_match_args(MatchResult&& m)
{
    if constexpr (N > 0) {
        auto expected = m.size() - 1;

        die_unless(
            N == expected,
            "incorrect match args: ",
            "expected ", expected,
            ", got ", N
        );
    }
}

template <typename CharT, typename MatchResult, typename... Args>
void
extract_submatches(MatchResult&& m, Args&&... args)
{
    constexpr auto nargs = sizeof...(args);

    check_match_args<nargs>(m);

    auto mit = m.begin();

    if constexpr (nargs > 0) {
        (extract_submatch<CharT>(*++mit, std::forward<Args>(args)), ...);
    }
}

template <
    typename CharT,
    typename MatchResult
>
void
extract_submatches(
    MatchResult&& m,
    std::vector<std::basic_string_view<CharT>>& vs
)
{
    auto mit = m.begin();

    while (++mit != m.end()) {
        vs.push_back(std::string_view{mit->first, mit->second});
    }
}

} // namespace detail

template <typename CharT, typename... Args>
bool
full_match(
    std::basic_string_view<CharT> e,
    const std::basic_regex<CharT>& re,
    Args&&... args
)
{
    std::cmatch m;

    bool match = std::regex_match(e.data(), e.data() + e.size(), m, re);

    if (match) {
        detail::extract_submatches<CharT>(m, std::forward<Args>(args)...);
    }

    return match;
}

template <typename CharT, typename... Args>
bool
full_match(
    std::basic_string_view<CharT> e,
    std::basic_string_view<CharT> pat,
    Args&&... args
)
{
    std::basic_regex<CharT> re(pat.data(), pat.size());

    return full_match(e, re, std::forward<Args>(args)...);
}

template <typename CharT, typename... Args>
bool
full_match(const std::basic_string<CharT>& e, Args&&... args)
{
    return
        full_match(
            std::string_view{ e.data(), e.size() },
            std::forward<Args>(args)...
        );
}

template <typename CharT, typename... Args>
bool
partial_match(
    std::basic_string_view<CharT> e,
    std::basic_string_view<CharT> pat,
    Args&&... args
)
{
    std::cmatch m;
    std::regex re(pat.data(), pat.size());

    bool match = std::regex_search(e.begin(), e.end(), m, re);

    if (match) {
        detail::extract_submatches(m, std::forward<Args>(args)...);
    }

    return match;
}

}
