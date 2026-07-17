#ifndef CUCUMBER_GHERKIN_UTILS_HPP
#define CUCUMBER_GHERKIN_UTILS_HPP

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244)
#endif

#include <cstddef>
#include <cstdint>
#include <regex>
#include <string>
#include <string_view>

namespace cucumber::gherkin
{

    namespace detail
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,cppcoreguidelines-pro-bounds-pointer-arithmetic)

        using utf8_ptr = const unsigned char*;

        // Sentinel returned by utf8_next for an invalid/incomplete byte sequence.
        inline constexpr char32_t invalidCodepoint = char32_t(-1);

        // Decodes the next Unicode code point from a UTF-8 stream, advancing ptr.
        // Returns invalid_codepoint and advances ptr by one for invalid sequences.
        inline char32_t Utf8Next(utf8_ptr& ptr, utf8_ptr end)
        {
            if (*ptr < 0x80)
            {
                return *ptr++;
            }
            if ((*ptr & 0xE0) == 0xC0 && (end - ptr) >= 2 && (ptr[1] & 0xC0) == 0x80)
            {
                auto byte0 = static_cast<char32_t>(*ptr++ & 0x1F);
                auto byte1 = static_cast<char32_t>(*ptr++ & 0x3F);
                return (byte0 << 6) | byte1;
            }
            if ((*ptr & 0xF0) == 0xE0 && (end - ptr) >= 3 && (ptr[1] & 0xC0) == 0x80 && (ptr[2] & 0xC0) == 0x80)
            {
                auto byte0 = static_cast<char32_t>(*ptr++ & 0x0F);
                auto byte1 = static_cast<char32_t>(*ptr++ & 0x3F);
                auto byte2 = static_cast<char32_t>(*ptr++ & 0x3F);
                return (byte0 << 12) | (byte1 << 6) | byte2;
            }
            if ((*ptr & 0xF8) == 0xF0 && (end - ptr) >= 4 && (ptr[1] & 0xC0) == 0x80 && (ptr[2] & 0xC0) == 0x80 && (ptr[3] & 0xC0) == 0x80)
            {
                auto byte0 = static_cast<char32_t>(*ptr++ & 0x07);
                auto byte1 = static_cast<char32_t>(*ptr++ & 0x3F);
                auto byte2 = static_cast<char32_t>(*ptr++ & 0x3F);
                auto byte3 = static_cast<char32_t>(*ptr++ & 0x3F);
                return (byte0 << 18) | (byte1 << 12) | (byte2 << 6) | byte3;
            }
            ++ptr; // skip invalid byte
            return invalidCodepoint;
        }

        // Appends a Unicode code point to a UTF-8 string.
        inline void Utf8Append(std::string& out, char32_t codepoint)
        {
            if (codepoint < 0x80)
            {
                out += static_cast<char>(codepoint);
            }
            else if (codepoint < 0x800)
            {
                out += static_cast<char>(0xC0 | (codepoint >> 6));
                out += static_cast<char>(0x80 | (codepoint & 0x3F));
            }
            else if (codepoint < 0x10000)
            {
                out += static_cast<char>(0xE0 | (codepoint >> 12));
                out += static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F));
                out += static_cast<char>(0x80 | (codepoint & 0x3F));
            }
            else
            {
                out += static_cast<char>(0xF0 | (codepoint >> 18));
                out += static_cast<char>(0x80 | ((codepoint >> 12) & 0x3F));
                out += static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F));
                out += static_cast<char>(0x80 | (codepoint & 0x3F));
            }
        }

        // Decodes the next Unicode code point from a wide string, advancing ptr.
        // Handles UTF-16 surrogate pairs on Windows; reads directly on Linux/macOS.
        inline char32_t WcharNext(const wchar_t*& ptr, const wchar_t* end)
        {
            if constexpr (sizeof(wchar_t) == 2)
            {
                // UTF-16 (Windows)
                const auto wideChar = static_cast<char32_t>(*ptr++);
                if (wideChar >= 0xD800 && wideChar <= 0xDBFF && ptr < end)
                {
                    const auto surrogateLow = static_cast<char32_t>(*ptr);
                    if (surrogateLow >= 0xDC00 && surrogateLow <= 0xDFFF)
                    {
                        ++ptr;
                        return 0x10000 + ((wideChar - 0xD800) << 10) + (surrogateLow - 0xDC00);
                    }
                }
                return wideChar; // lone surrogate or BMP character
            }
            else
            {
                // UTF-32 (Linux/macOS)
                return static_cast<char32_t>(*ptr++);
            }
        }

        // Appends a Unicode code point to a wide string.
        // Emits a surrogate pair on Windows; stores directly on Linux/macOS.
        inline void WcharAppend(std::wstring& out, char32_t codepoint)
        {
            if constexpr (sizeof(wchar_t) == 2)
            {
                // UTF-16 (Windows)
                if (codepoint < 0x10000)
                {
                    out += static_cast<wchar_t>(codepoint);
                }
                else
                {
                    codepoint -= 0x10000;
                    out += static_cast<wchar_t>(0xD800 | (codepoint >> 10));
                    out += static_cast<wchar_t>(0xDC00 | (codepoint & 0x3FF));
                }
            }
            else
            {
                // UTF-32 (Linux/macOS)
                out += static_cast<wchar_t>(codepoint);
            }
        }

    }

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,cppcoreguidelines-pro-bounds-pointer-arithmetic)

    // NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-pro-type-reinterpret-cast)
    inline std::wstring ToWide(const std::string& source)
    {
        std::wstring result;
        result.reserve(source.size());

        const auto* ptr = reinterpret_cast<const unsigned char*>(source.data());
        const auto* end = ptr + source.size();

        while (ptr < end)
        {
            const auto codepoint = detail::Utf8Next(ptr, end);
            if (codepoint != detail::invalidCodepoint)
            {
                detail::WcharAppend(result, codepoint);
            }
        }

        return result;
    }

    inline std::string ToNarrow(const std::wstring& wideString)
    {
        std::string result;
        result.reserve(wideString.size() * 3);

        const auto* ptr = wideString.data();
        const auto* end = ptr + wideString.size();

        while (ptr < end)
        {
            detail::Utf8Append(result, detail::WcharNext(ptr, end));
        }

        return result;
    }
    // NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-pro-type-reinterpret-cast)

    enum class RePattern : std::uint8_t
    {
        none,
        allSpaces,
        spacesNoNl,
        crlf,
        cr,
        bol,
        eol
    };

    template<typename CharT>
    struct RePatterns
    {
        static auto Convert(std::string_view view)
        {
            if constexpr (sizeof(CharT) > sizeof(char))
            {
                return ToWide(std::string(view));
            }
            else
            {
                return std::string(view);
            }
        }

        static auto Get(RePattern pattern)
        {
            using namespace std::literals;
            std::string_view view;

            switch (pattern)
            {
                case RePattern::none:
                    break;
                case RePattern::allSpaces:
                    view = R"([ \t\n\v\f\r\u0085\u00A0]+)";
                    break;
                case RePattern::spacesNoNl:
                    view = R"([ \t\v\f\r\u0085\u00A0]+)";
                    break;
                case RePattern::crlf:
                    view = R"(\r\n)";
                case RePattern::cr:
                    view = R"(\r)";
                    break;
                case RePattern::bol:
                    view = "^"sv;
                    break;
                case RePattern::eol:
                    view = "$"sv;
                    break;
            }

            return Convert(view);
        }
    };

    template<typename CharT>
    struct StripPattern
    {
        using s_type = std::basic_string<CharT>;
        using sv_type = std::basic_string_view<CharT>;
        using pats = RePatterns<CharT>;

        StripPattern(RePattern prefix, sv_type chars)
            : StripPattern(prefix, chars, RePattern::none)
        {}

        StripPattern(sv_type chars, RePattern suffix)
            : StripPattern(RePattern::none, chars, suffix)
        {}

        StripPattern(sv_type chars)
            : StripPattern(RePattern::none, chars, RePattern::none)
        {}

        StripPattern(RePattern prefix, sv_type chars, RePattern suffix)
        {
            if (prefix != RePattern::none)
            {
                s = pats::Get(prefix);
            }

            s += chars;

            if (suffix != RePattern::none)
            {
                s += pats::Get(suffix);
            }
        }

        [[nodiscard]] const s_type& Str() const
        {
            return s;
        }

        s_type s;
    };

    template<typename CharT>
    std::basic_string_view<CharT> AsView(const std::basic_string<CharT>& source)
    {
        return { source.data(), source.size() };
    }

    std::size_t CodepointCount(std::string_view text);

    std::string Slurp(const std::string& path);

    void Replace(std::string& source, std::string_view what, std::string_view with);

    std::string Replace(const std::string& source, std::string_view what, std::string_view with);

    template<typename CharT>
    std::basic_string<CharT> Strip(std::basic_string_view<CharT> what, const StripPattern<CharT>& pattern)
    {
        std::basic_regex<CharT> const regex(pattern.Str());
        std::basic_string<CharT> const empty;
        std::basic_string<CharT> result;

        std::regex_replace(std::back_inserter(result), what.begin(), what.end(), regex, empty);

        return result;
    }

    template<typename CharT>
    std::basic_string<CharT> Lstrip(std::basic_string_view<CharT> text, RePattern pattern = RePattern::allSpaces)
    {
        return Strip(text, StripPattern<CharT>(RePattern::bol, RePatterns<CharT>::Get(pattern)));
    }

    template<typename CharT>
    std::basic_string<CharT> Lstrip(const std::basic_string<CharT>& text, RePattern pattern = RePattern::allSpaces)
    {
        return Lstrip(AsView(text), pattern);
    }

    template<typename CharT>
    std::basic_string<CharT> Rstrip(std::basic_string_view<CharT> text, RePattern pattern = RePattern::allSpaces)
    {
        return Strip(text, StripPattern<CharT>(RePatterns<CharT>::Get(pattern), RePattern::eol));
    }

    template<typename CharT>
    std::basic_string<CharT> Rstrip(const std::basic_string<CharT>& text, RePattern pattern = RePattern::allSpaces)
    {
        return Rstrip(AsView(text), pattern);
    }

    template<typename CharT>
    std::basic_string<CharT> Strip(std::basic_string_view<CharT> text, RePattern pattern = RePattern::allSpaces)
    {
        return Lstrip(Rstrip(text, pattern), pattern);
    }

    template<typename CharT>
    std::basic_string<CharT> Strip(const std::basic_string<CharT>& text, RePattern pattern = RePattern::allSpaces)
    {
        return Strip(AsView(text), pattern);
    }

    template<typename C>
    struct Reverse
    {
        Reverse(C& container)
            : c(container)
        {}

        auto Begin()
        {
            return c.rbegin();
        }

        auto End()
        {
            return c.rend();
        }

        C& c; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
    };

}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
