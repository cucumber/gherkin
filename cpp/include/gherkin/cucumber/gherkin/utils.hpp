#ifndef CUCUMBER_GHERKIN_UTILS_HPP
#define CUCUMBER_GHERKIN_UTILS_HPP

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244)
#endif

#include <cstddef>
#include <regex>
#include <string>
#include <string_view>

namespace cucumber::gherkin
{

    namespace detail
    {

        using utf8_ptr = const unsigned char*;

        // Sentinel returned by utf8_next for an invalid/incomplete byte sequence.
        inline constexpr char32_t invalid_codepoint = char32_t(-1);

        // Decodes the next Unicode code point from a UTF-8 stream, advancing ptr.
        // Returns invalid_codepoint and advances ptr by one for invalid sequences.
        inline char32_t utf8_next(utf8_ptr& ptr, utf8_ptr end)
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
            return invalid_codepoint;
        }

        // Appends a Unicode code point to a UTF-8 string.
        inline void utf8_append(std::string& out, char32_t codepoint)
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
        inline char32_t wchar_next(const wchar_t*& ptr, const wchar_t* end)
        {
            if constexpr (sizeof(wchar_t) == 2)
            {
                // UTF-16 (Windows)
                const auto wide_char = static_cast<char32_t>(*ptr++);
                if (wide_char >= 0xD800 && wide_char <= 0xDBFF && ptr < end)
                {
                    const auto surrogate_low = static_cast<char32_t>(*ptr);
                    if (surrogate_low >= 0xDC00 && surrogate_low <= 0xDFFF)
                    {
                        ++ptr;
                        return 0x10000 + ((wide_char - 0xD800) << 10) + (surrogate_low - 0xDC00);
                    }
                }
                return wide_char; // lone surrogate or BMP character
            }
            else
            {
                // UTF-32 (Linux/macOS)
                return static_cast<char32_t>(*ptr++);
            }
        }

        // Appends a Unicode code point to a wide string.
        // Emits a surrogate pair on Windows; stores directly on Linux/macOS.
        inline void wchar_append(std::wstring& out, char32_t codepoint)
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

    inline std::wstring to_wide(const std::string& source)
    {
        std::wstring result;
        result.reserve(source.size());

        const auto* ptr = reinterpret_cast<const unsigned char*>(source.data());
        const auto* end = ptr + source.size();

        while (ptr < end)
        {
            const auto codepoint = detail::utf8_next(ptr, end);
            if (codepoint != detail::invalid_codepoint)
            {
                detail::wchar_append(result, codepoint);
            }
        }

        return result;
    }

    inline std::string to_narrow(const std::wstring& wide_string)
    {
        std::string result;
        result.reserve(wide_string.size() * 3);

        const auto* ptr = wide_string.data();
        const auto* end = ptr + wide_string.size();

        while (ptr < end)
        {
            detail::utf8_append(result, detail::wchar_next(ptr, end));
        }

        return result;
    }

    enum class RePattern
    {
        none,
        all_spaces,
        spaces_no_nl,
        crlf,
        cr,
        bol,
        eol
    };

    template<typename CharT>
    struct RePatterns
    {
        static auto convert(std::string_view view)
        {
            if constexpr (sizeof(CharT) > sizeof(char))
            {
                return to_wide(std::string(view));
            }
            else
            {
                return std::string(view);
            }
        }

        static auto get(RePattern pattern)
        {
            using namespace std::literals;
            std::string_view view;

            switch (pattern)
            {
                case RePattern::none:
                    break;
                case RePattern::all_spaces:
                    view = "[ \\t\\n\\v\\f\\r\\u0085\\u00A0]+"sv;
                    break;
                case RePattern::spaces_no_nl:
                    view = "[ \\t\\v\\f\\r\\u0085\\u00A0]+"sv;
                    break;
                case RePattern::crlf:
                    view = "\\r\\n"sv;
                case RePattern::cr:
                    view = "\\r"sv;
                    break;
                case RePattern::bol:
                    view = "^"sv;
                    break;
                case RePattern::eol:
                    view = "$"sv;
                    break;
            }

            return convert(view);
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
                s_ = pats::get(prefix);
            }

            s_ += chars;

            if (suffix != RePattern::none)
            {
                s_ += pats::get(suffix);
            }
        }

        const s_type& str() const
        {
            return s_;
        }

        s_type s_;
    };

    template<typename CharT>
    std::basic_string_view<CharT> as_view(const std::basic_string<CharT>& source)
    {
        return { source.data(), source.size() };
    }

    std::size_t codepoint_count(std::string_view text);

    std::string slurp(const std::string& path);

    void replace(std::string& source, std::string_view what, std::string_view with);

    std::string replace(const std::string& source, std::string_view what, std::string_view with);

    template<typename CharT>
    std::basic_string<CharT> strip(std::basic_string_view<CharT> what, const StripPattern<CharT>& pattern)
    {
        std::basic_regex<CharT> regex(pattern.str());
        std::basic_string<CharT> empty;
        std::basic_string<CharT> result;

        std::regex_replace(std::back_inserter(result), what.begin(), what.end(), regex, empty);

        return result;
    }

    template<typename CharT>
    std::basic_string<CharT> lstrip(std::basic_string_view<CharT> text, RePattern pattern = RePattern::all_spaces)
    {
        return strip(text, StripPattern<CharT>(RePattern::bol, RePatterns<CharT>::get(pattern)));
    }

    template<typename CharT>
    std::basic_string<CharT> lstrip(const std::basic_string<CharT>& text, RePattern pattern = RePattern::all_spaces)
    {
        return lstrip(as_view(text), pattern);
    }

    template<typename CharT>
    std::basic_string<CharT> rstrip(std::basic_string_view<CharT> text, RePattern pattern = RePattern::all_spaces)
    {
        return strip(text, StripPattern<CharT>(RePatterns<CharT>::get(pattern), RePattern::eol));
    }

    template<typename CharT>
    std::basic_string<CharT> rstrip(const std::basic_string<CharT>& text, RePattern pattern = RePattern::all_spaces)
    {
        return rstrip(as_view(text), pattern);
    }

    template<typename CharT>
    std::basic_string<CharT> strip(std::basic_string_view<CharT> text, RePattern pattern = RePattern::all_spaces)
    {
        return lstrip(rstrip(text, pattern), pattern);
    }

    template<typename CharT>
    std::basic_string<CharT> strip(const std::basic_string<CharT>& text, RePattern pattern = RePattern::all_spaces)
    {
        return strip(as_view(text), pattern);
    }

    template<typename C>
    struct Reverse
    {
        Reverse(C& container)
            : c_(container)
        {}

        auto begin()
        {
            return c_.rbegin();
        }

        auto end()
        {
            return c_.rend();
        }

        C& c_;
    };

}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
