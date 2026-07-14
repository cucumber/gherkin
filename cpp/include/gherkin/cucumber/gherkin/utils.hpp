#pragma once

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244)
#endif

#include <cstddef>
#include <regex>
#include <string>
#include <string_view>

namespace cucumber::gherkin {

namespace detail {

using utf8_ptr = const unsigned char *;

// Sentinel returned by utf8_next for an invalid/incomplete byte sequence.
inline constexpr char32_t invalid_codepoint = char32_t(-1);

// Decodes the next Unicode code point from a UTF-8 stream, advancing p.
// Returns invalid_codepoint and advances p by one for invalid sequences.
inline char32_t utf8_next(utf8_ptr &p, utf8_ptr end) {
  if (*p < 0x80) {
    return *p++;
  }
  if ((*p & 0xE0) == 0xC0 && (end - p) >= 2 && (p[1] & 0xC0) == 0x80) {
    auto b0 = static_cast<char32_t>(*p++ & 0x1F);
    auto b1 = static_cast<char32_t>(*p++ & 0x3F);
    return (b0 << 6) | b1;
  }
  if ((*p & 0xF0) == 0xE0 && (end - p) >= 3 && (p[1] & 0xC0) == 0x80 &&
      (p[2] & 0xC0) == 0x80) {
    auto b0 = static_cast<char32_t>(*p++ & 0x0F);
    auto b1 = static_cast<char32_t>(*p++ & 0x3F);
    auto b2 = static_cast<char32_t>(*p++ & 0x3F);
    return (b0 << 12) | (b1 << 6) | b2;
  }
  if ((*p & 0xF8) == 0xF0 && (end - p) >= 4 && (p[1] & 0xC0) == 0x80 &&
      (p[2] & 0xC0) == 0x80 && (p[3] & 0xC0) == 0x80) {
    auto b0 = static_cast<char32_t>(*p++ & 0x07);
    auto b1 = static_cast<char32_t>(*p++ & 0x3F);
    auto b2 = static_cast<char32_t>(*p++ & 0x3F);
    auto b3 = static_cast<char32_t>(*p++ & 0x3F);
    return (b0 << 18) | (b1 << 12) | (b2 << 6) | b3;
  }
  ++p; // skip invalid byte
  return invalid_codepoint;
}

// Appends a Unicode code point to a UTF-8 string.
inline void utf8_append(std::string &out, char32_t cp) {
  if (cp < 0x80) {
    out += static_cast<char>(cp);
  } else if (cp < 0x800) {
    out += static_cast<char>(0xC0 | (cp >> 6));
    out += static_cast<char>(0x80 | (cp & 0x3F));
  } else if (cp < 0x10000) {
    out += static_cast<char>(0xE0 | (cp >> 12));
    out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
    out += static_cast<char>(0x80 | (cp & 0x3F));
  } else {
    out += static_cast<char>(0xF0 | (cp >> 18));
    out += static_cast<char>(0x80 | ((cp >> 12) & 0x3F));
    out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
    out += static_cast<char>(0x80 | (cp & 0x3F));
  }
}

// Decodes the next Unicode code point from a wide string, advancing p.
// Handles UTF-16 surrogate pairs on Windows; reads directly on Linux/macOS.
inline char32_t wchar_next(const wchar_t *&p, const wchar_t *end) {
  if constexpr (sizeof(wchar_t) == 2) {
    // UTF-16 (Windows)
    const auto w = static_cast<char32_t>(*p++);
    if (w >= 0xD800 && w <= 0xDBFF && p < end) {
      const auto w2 = static_cast<char32_t>(*p);
      if (w2 >= 0xDC00 && w2 <= 0xDFFF) {
        ++p;
        return 0x10000 + ((w - 0xD800) << 10) + (w2 - 0xDC00);
      }
    }
    return w; // lone surrogate or BMP character
  } else {
    // UTF-32 (Linux/macOS)
    return static_cast<char32_t>(*p++);
  }
}

// Appends a Unicode code point to a wide string.
// Emits a surrogate pair on Windows; stores directly on Linux/macOS.
inline void wchar_append(std::wstring &out, char32_t cp) {
  if constexpr (sizeof(wchar_t) == 2) {
    // UTF-16 (Windows)
    if (cp < 0x10000) {
      out += static_cast<wchar_t>(cp);
    } else {
      cp -= 0x10000;
      out += static_cast<wchar_t>(0xD800 | (cp >> 10));
      out += static_cast<wchar_t>(0xDC00 | (cp & 0x3FF));
    }
  } else {
    // UTF-32 (Linux/macOS)
    out += static_cast<wchar_t>(cp);
  }
}

} // namespace detail

inline std::wstring to_wide(const std::string &s) {
  std::wstring result;
  result.reserve(s.size());

  const auto *p = reinterpret_cast<const unsigned char *>(s.data());
  const auto *end = p + s.size();

  while (p < end) {
    const auto cp = detail::utf8_next(p, end);
    if (cp != detail::invalid_codepoint) {
      detail::wchar_append(result, cp);
    }
  }

  return result;
}

inline std::string to_narrow(const std::wstring &ws) {
  std::string result;
  result.reserve(ws.size() * 3);

  const auto *p = ws.data();
  const auto *end = p + ws.size();

  while (p < end) {
    detail::utf8_append(result, detail::wchar_next(p, end));
  }

  return result;
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
