#pragma once

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4996)
#pragma warning(disable : 4244)
#endif

#include <locale>
#include <codecvt>
#include <string>
#include <string_view>
#include <regex>

namespace cucumber::gherkin {

// utility wrapper to adapt locale-bound facets for wstring/wbuffer convert
template <class Facet>
struct deletable_facet : Facet
{
    template <class... Args>
    deletable_facet(Args&&... args)
    : Facet(std::forward<Args>(args)...)
    {}

    ~deletable_facet()
    {}
};

inline
std::wstring
to_wide(const std::string& s)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>,char32_t> cv;

    auto ws = cv.from_bytes(s);

    return {ws.begin(), ws.end()};
}

inline
std::string
to_narrow(const std::wstring& ws)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>,char32_t> cv;

    std::u32string s{ws.begin(), ws.end()};

    return cv.to_bytes(s);
}

enum class re_pattern
{
    none,
    all_spaces,
    spaces_no_nl,
    crlf,
    cr,
    bol,
    eol
};

template <typename CharT>
struct re_patterns
{
    static
    auto
    convert(std::string_view sv)
    {
        if constexpr (sizeof(CharT) > sizeof(char)) {
            return to_wide(std::string(sv));
        } else {
            return std::string(sv);
        }
    }

    static
    auto get(re_pattern p)
    {
        using namespace std::literals;
        std::string_view sv;

        switch (p) {
            case re_pattern::none:
            break;
            case re_pattern::all_spaces:
            sv = "[ \\t\\n\\v\\f\\r\\u0085\\u00A0]+"sv;
            break;
            case re_pattern::spaces_no_nl:
            sv = "[ \\t\\v\\f\\r\\u0085\\u00A0]+"sv;
            break;
            case re_pattern::crlf:
            sv = "\\r\\n"sv;
            case re_pattern::cr:
            sv = "\\r"sv;
            break;
            case re_pattern::bol:
            sv = "^"sv;
            break;
            case re_pattern::eol:
            sv = "$"sv;
            break;
        }

        return convert(sv);
    }
};

template <typename CharT>
struct strip_pattern
{
    using s_type = std::basic_string<CharT>;
    using sv_type = std::basic_string_view<CharT>;
    using pats = re_patterns<CharT>;

    strip_pattern(re_pattern prefix, sv_type chars)
    : strip_pattern(prefix, chars, re_pattern::none)
    {}

    strip_pattern(sv_type chars, re_pattern suffix)
    : strip_pattern(re_pattern::none, chars, suffix)
    {}

    strip_pattern(sv_type chars)
    : strip_pattern(re_pattern::none, chars, re_pattern::none)
    {}

    strip_pattern(re_pattern prefix, sv_type chars, re_pattern suffix)
    {
        if (prefix != re_pattern::none) {
            s_ = pats::get(prefix);
        }

        s_ += chars;

        if (suffix != re_pattern::none) {
            s_ += pats::get(suffix);
        }
    }

    const s_type& str() const
    { return s_; }

    s_type s_;
};

template <typename CharT>
std::basic_string_view<CharT>
as_view(const std::basic_string<CharT>& s)
{ return { s.data(), s.size() }; }

std::size_t
codepoint_count(std::string_view s);

std::string
slurp(const std::string& path);

void
replace(std::string& s, std::string_view what, std::string_view with);

std::string
replace(const std::string& s, std::string_view what, std::string_view with);

template <typename CharT>
std::basic_string<CharT>
strip(std::basic_string_view<CharT> what, const strip_pattern<CharT>& p)
{
    std::basic_regex<CharT> re(p.str());
    std::basic_string<CharT> empty;
    std::basic_string<CharT> result;

    std::regex_replace(
        std::back_inserter(result),
        what.begin(), what.end(),
        re,
        empty
    );

    return result;
}

template <typename CharT>
std::basic_string<CharT>
lstrip(
    std::basic_string_view<CharT> in,
    re_pattern p = re_pattern::all_spaces
)
{
    return
        strip(
            in,
            strip_pattern<CharT>(
                re_pattern::bol,
                re_patterns<CharT>::get(p)
            )
        );
}

template <typename CharT>
std::basic_string<CharT>
lstrip(
    const std::basic_string<CharT>& in,
    re_pattern p = re_pattern::all_spaces
)
{ return lstrip(as_view(in), p); }

template <typename CharT>
std::basic_string<CharT>
rstrip(
    std::basic_string_view<CharT> in,
    re_pattern p = re_pattern::all_spaces
)
{
    return
        strip(
            in,
            strip_pattern<CharT>(
                re_patterns<CharT>::get(p),
                re_pattern::eol
            )
        );
}

template <typename CharT>
std::basic_string<CharT>
rstrip(
    const std::basic_string<CharT>& in,
    re_pattern p = re_pattern::all_spaces
)
{ return rstrip(as_view(in), p); }

template <typename CharT>
std::basic_string<CharT>
strip(
    std::basic_string_view<CharT> in,
    re_pattern p = re_pattern::all_spaces
)
{ return lstrip(rstrip(in, p), p); }

template <typename CharT>
std::basic_string<CharT>
strip(
    const std::basic_string<CharT>& in,
    re_pattern p = re_pattern::all_spaces
)
{ return strip(as_view(in), p); }

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

#ifdef _MSC_VER
#pragma warning(pop)
#endif
