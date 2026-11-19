#ifndef CUCUMBER_GHERKIN_UTILS_HPP
#define CUCUMBER_GHERKIN_UTILS_HPP

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244)
#endif

#include "cucumber/gherkin/Regex.hpp"
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>

namespace cucumber::gherkin
{

    namespace detail
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,cppcoreguidelines-pro-bounds-pointer-arithmetic)

        using Utf8Ptr = const unsigned char*;

        // Sentinel returned by utf8_next for an invalid/incomplete byte sequence.
        inline constexpr char32_t invalidCodepoint = char32_t(-1);

        // Decodes the next Unicode code point from a UTF-8 stream, advancing ptr.
        // Returns invalid_codepoint and advances ptr by one for invalid sequences.
        inline char32_t Utf8Next(Utf8Ptr& ptr, Utf8Ptr end)
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
    inline std::wstring ToWide(std::string_view source)
    {
        std::wstring result;
        if (source.empty())
        {
            return result;
        }
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

    inline std::string ToNarrow(std::wstring_view wideString)
    {
        std::string result;
        if (wideString.empty())
        {
            return result;
        }
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
        eol,
    };

    template<typename CharT>
    struct RePatterns
    {
        static auto Convert(std::string_view view)
        {
            if constexpr (sizeof(CharT) > sizeof(char))
            {
                return ToWide(view);
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
        using SType = std::basic_string<CharT>;
        using SvType = std::basic_string_view<CharT>;
        using Pats = RePatterns<CharT>;

        StripPattern(RePattern prefix, SvType chars)
            : StripPattern(prefix, chars, RePattern::none)
        {}

        StripPattern(SvType chars, RePattern suffix)
            : StripPattern(RePattern::none, chars, suffix)
        {}

        StripPattern(SvType chars)
            : StripPattern(RePattern::none, chars, RePattern::none)
        {}

        StripPattern(RePattern prefix, SvType chars, RePattern suffix)
        {
            if (prefix != RePattern::none)
            {
                s = Pats::Get(prefix);
            }

            s += chars;

            if (suffix != RePattern::none)
            {
                s += Pats::Get(suffix);
            }
        }

        [[nodiscard]] const SType& Str() const
        {
            return s;
        }

        SType s;
    };

    template<typename CharT>
    std::basic_string_view<CharT> AsView(const std::basic_string<CharT>& source)
    {
        return { source.data(), source.size() };
    }

    [[nodiscard]] std::size_t CodepointCount(std::string_view text);

    [[nodiscard]] std::string Slurp(const std::string& path);

    void Replace(std::string& source, std::string_view what, std::string_view with);

    [[nodiscard]] std::string Replace(const std::string& source, std::string_view what, std::string_view with);

    template<typename CharT>
    std::basic_string<CharT> Strip(std::basic_string_view<CharT> what, const StripPattern<CharT>& pattern)
    {
        return Substitute(std::basic_string<CharT>(what), pattern.Str());
    }

    namespace detail
    {
        template<typename CharT, bool Left>
        std::basic_string_view<CharT> TrimView(std::basic_string_view<CharT> text, RePattern pattern)
        {
            switch (pattern)
            {
                case RePattern::none:
                case RePattern::bol:
                case RePattern::eol:
                    return text;
                // RePatterns::Get currently maps crlf to a single CR, as it does cr.
                case RePattern::crlf:
                case RePattern::cr:
                    if (!text.empty() && (Left ? text.front() : text.back()) == static_cast<CharT>('\r'))
                    {
                        if constexpr (Left)
                        {
                            text.remove_prefix(1);
                        }
                        else
                        {
                            text.remove_suffix(1);
                        }
                    }
                    return text;
                case RePattern::allSpaces:
                case RePattern::spacesNoNl:
                    break;
                default:
                    throw std::out_of_range("Invalid trimming pattern");
            }

            const auto isSpace = [pattern](CharT character)
            {
                return character == ' ' || character == '\t' || character == '\v' || character == '\f' || character == '\r' ||
                       character == static_cast<CharT>(U'\u0085') || character == static_cast<CharT>(U'\u00a0') ||
                       (pattern == RePattern::allSpaces && character == '\n');
            };
            while (!text.empty() && isSpace(Left ? text.front() : text.back()))
            {
                if constexpr (Left)
                {
                    text.remove_prefix(1);
                }
                else
                {
                    text.remove_suffix(1);
                }
            }
            return text;
        }
    }

    template<typename CharT>
    std::basic_string<CharT> Lstrip(std::basic_string_view<CharT> text, RePattern pattern = RePattern::allSpaces)
    {
        return std::basic_string<CharT>(detail::TrimView<CharT, true>(text, pattern));
    }

    template<typename CharT>
    std::basic_string<CharT> Lstrip(const std::basic_string<CharT>& text, RePattern pattern = RePattern::allSpaces)
    {
        return Lstrip(AsView(text), pattern);
    }

    template<typename CharT>
    std::basic_string<CharT> Rstrip(std::basic_string_view<CharT> text, RePattern pattern = RePattern::allSpaces)
    {
        return std::basic_string<CharT>(detail::TrimView<CharT, false>(text, pattern));
    }

    template<typename CharT>
    std::basic_string<CharT> Rstrip(const std::basic_string<CharT>& text, RePattern pattern = RePattern::allSpaces)
    {
        return Rstrip(AsView(text), pattern);
    }

    template<typename CharT>
    std::basic_string<CharT> Strip(std::basic_string_view<CharT> text, RePattern pattern = RePattern::allSpaces)
    {
        return std::basic_string<CharT>(detail::TrimView<CharT, true>(detail::TrimView<CharT, false>(text, pattern), pattern));
    }

    template<typename CharT>
    std::basic_string<CharT> Strip(const std::basic_string<CharT>& text, RePattern pattern = RePattern::allSpaces)
    {
        return Strip(AsView(text), pattern);
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
