#include "cucumber/gherkin/Regex.hpp"
#include "cucumber/gherkin/Types.hpp"
#include <memory>
#include <re2/stringpiece.h>
#include <string>
#include <string_view>

#ifdef CUCUMBER_GHERKIN_HAS_RE2
#include "cucumber/gherkin/Utils.hpp"
#include <array>
#include <cstddef>
#include <re2/re2.h>
#include <stdexcept>
#include <vector>
#else
#include <regex>
#endif

namespace cucumber::gherkin
{
    namespace detail
    {
        class WideRegexStrategy
        {
        public:
            WideRegexStrategy() = default;
            virtual ~WideRegexStrategy() = default;
            WideRegexStrategy(const WideRegexStrategy&) = delete;
            WideRegexStrategy& operator=(const WideRegexStrategy&) = delete;
            WideRegexStrategy(WideRegexStrategy&&) = delete;
            WideRegexStrategy& operator=(WideRegexStrategy&&) = delete;

            [[nodiscard]] virtual std::wstring Replace(std::wstring_view source, std::wstring_view replacement) const = 0;
        };

        class RegexStrategy
        {
        public:
            RegexStrategy() = default;
            virtual ~RegexStrategy() = default;
            RegexStrategy(const RegexStrategy&) = delete;
            RegexStrategy& operator=(const RegexStrategy&) = delete;
            RegexStrategy(RegexStrategy&&) = delete;
            RegexStrategy& operator=(RegexStrategy&&) = delete;

            [[nodiscard]] virtual RegexResult Match(std::string_view expression, bool full) const = 0;
            [[nodiscard]] virtual std::string Replace(std::string_view source, std::string_view replacement) const = 0;
            [[nodiscard]] virtual Strings Split(std::string_view expression) const = 0;
        };

#ifndef CUCUMBER_GHERKIN_HAS_RE2
        class StdWideRegexStrategy final : public WideRegexStrategy
        {
        public:
            explicit StdWideRegexStrategy(std::wstring_view pattern)
                : regex(pattern.data() == nullptr ? L"" : pattern.data(), pattern.size())
            {}

            [[nodiscard]] std::wstring Replace(std::wstring_view source, std::wstring_view replacement) const override
            {
                return std::regex_replace(std::wstring(source), regex, std::wstring(replacement));
            }

        private:
            std::wregex regex;
        };

        class StdRegexStrategy final : public RegexStrategy
        {
        public:
            explicit StdRegexStrategy(std::string_view pattern)
                : regex(pattern.data() == nullptr ? "" : pattern.data(), pattern.size())
            {}

            [[nodiscard]] RegexResult Match(std::string_view expression, bool full) const override
            {
                if (expression.data() == nullptr)
                {
                    expression = "";
                }

                std::match_results<const char*> matches;
                RegexResult result;

                result.match = full ? std::regex_match(expression.begin(), expression.end(), matches, regex)
                                    : std::regex_search(expression.begin(), expression.end(), matches, regex);

                if (result.match)
                {
                    for (const auto& match : matches)
                    {
                        result.matches.emplace_back(match.first, match.length());
                    }
                }

                return result;
            }

            [[nodiscard]] std::string Replace(std::string_view source, std::string_view replacement) const override
            {
                return std::regex_replace(std::string(source), regex, std::string(replacement));
            }

            [[nodiscard]] Strings Split(std::string_view expression) const override
            {
                if (expression.empty())
                {
                    return {};
                }

                const std::string source(expression);

                return { std::sregex_token_iterator(source.begin(), source.end(), regex, -1), std::sregex_token_iterator() };
            }

        private:
            std::regex regex;
        };
#else
        namespace
        {
            std::string Re2Pattern(std::string_view pattern)
            {
                std::string result;
                bool inClass = false;
                for (std::size_t i = 0; i < pattern.size(); ++i)
                {
                    if (pattern.at(i) == '\\' && i + 1 < pattern.size())
                    {
                        const char escaped = pattern.at(++i);
                        if (escaped == 'u' && i + 4 < pattern.size())
                        {
                            result += "\\x{";
                            result += pattern.substr(i + 1, 4);
                            result += '}';
                            i += 4;
                        }
                        else if (escaped == 's')
                        {
                            // RE2's Perl whitespace class omits vertical tab.
                            result += inClass ? R"( \t\n\v\f\r)" : R"([ \t\n\v\f\r])";
                        }
                        else if (escaped == 'S' && !inClass)
                        {
                            result += R"([^ \t\n\v\f\r])";
                        }
                        else
                        {
                            result += '\\';
                            result += escaped;
                        }
                    }
                    else
                    {
                        if (pattern.at(i) == '[')
                        {
                            inClass = true;
                        }
                        else if (pattern.at(i) == ']')
                        {
                            inClass = false;
                        }
                        result += pattern.at(i);
                    }
                }

                return result;
            }

            re2::RE2::Options Re2Options(bool utf8)
            {
                re2::RE2::Options options;
                options.set_log_errors(false);

                // Narrow std::regex operates on bytes, not Unicode code points.
                options.set_encoding(utf8 ? re2::RE2::Options::EncodingUTF8 : re2::RE2::Options::EncodingLatin1);

                return options;
            }

            void AppendReplacement(std::string& output, std::string_view replacement, const StringViews& matches, std::string_view prefix,
                std::string_view suffix)
            {
                for (std::size_t i = 0; i < replacement.size(); ++i)
                {
                    if (replacement.at(i) != '$' || i + 1 == replacement.size())
                    {
                        output += replacement.at(i);
                        continue;
                    }
                    switch (replacement.at(i + 1))
                    {
                        case '$':
                            output += '$';
                            ++i;
                            continue;
                        case '&':
                            output += matches.front();
                            ++i;
                            continue;
                        case '`':
                            output += prefix;
                            ++i;
                            continue;
                        case '\'':
                            output += suffix;
                            ++i;
                            continue;
                        default:
                            break;
                    }
                    const char next = replacement.at(i + 1);
                    if (next >= '0' && next <= '9')
                    {
                        constexpr std::size_t decimalBase = 10;
                        ++i;
                        auto index = static_cast<std::size_t>(next - '0');
                        if (i + 1 < replacement.size() && replacement.at(i + 1) >= '0' && replacement.at(i + 1) <= '9')
                        {
                            index = (index * decimalBase) + static_cast<std::size_t>(replacement.at(++i) - '0');
                        }

                        if (index < matches.size())
                        {
                            output += matches.at(index);
                        }
                    }
                    else
                    {
                        output += '$';
                    }
                }
            }

            class Re2RegexStrategy final
                : public RegexStrategy
                , public WideRegexStrategy
            {
            public:
                explicit Re2RegexStrategy(std::string_view pattern, bool utf8 = false)
                    : regex(Re2Pattern(pattern), Re2Options(utf8))
                {
                    if (!regex.ok())
                    {
                        throw std::invalid_argument("Invalid RE2 pattern: " + regex.error());
                    }
                }

                [[nodiscard]] RegexResult Match(std::string_view expression, bool full) const override
                {
                    RegexResult result;

                    MatchAt(expression, 0, full ? re2::RE2::ANCHOR_BOTH : re2::RE2::UNANCHORED, true, result);

                    return result;
                }

                [[nodiscard]] std::string Replace(std::string_view source, std::string_view replacement) const override
                {
                    std::string result;
                    std::size_t copied = 0;

                    ForEachMatch(source,
                        [&](const RegexResult& match, std::size_t position)
                        {
                            result += source.substr(copied, position - copied);
                            const auto end = position + match.matches.front().size();

                            AppendReplacement(result, replacement, match.matches, source.substr(copied, position - copied),
                                source.substr(end));
                            copied = end;
                        });

                    result += source.substr(copied);

                    return result;
                }

                [[nodiscard]] std::wstring Replace(std::wstring_view source, std::wstring_view replacement) const override
                {
                    return ToWide(Replace(ToNarrow(source), ToNarrow(replacement)));
                }

                [[nodiscard]] Strings Split(std::string_view expression) const override
                {
                    if (expression.empty())
                    {
                        return {};
                    }

                    Strings result;
                    std::size_t copied = 0;

                    ForEachMatch(
                        expression,
                        [&](const RegexResult& match, std::size_t position)
                        {
                            result.emplace_back(expression.substr(copied, position - copied));
                            copied = position + match.matches.front().size();
                        },
                        false);

                    if (copied < expression.size() || result.empty())
                    {
                        result.emplace_back(expression.substr(copied));
                    }

                    return result;
                }

            private:
                void MatchAt(std::string_view expression, std::size_t offset, re2::RE2::Anchor anchor, bool captureGroups,
                    RegexResult& result) const
                {
                    if (expression.data() == nullptr)
                    {
                        expression = "";
                    }

                    constexpr std::size_t inlineCaptures = 8;
                    std::array<re2::StringPiece, inlineCaptures> localMatches;
                    const auto count = captureGroups ? static_cast<std::size_t>(regex.NumberOfCapturingGroups()) + 1 : 1;

                    std::vector<re2::StringPiece> extraMatches;
                    auto* matches = localMatches.data();

                    if (count > localMatches.size())
                    {
                        extraMatches.resize(count);
                        matches = extraMatches.data();
                    }

                    result.matches.clear();
                    result.match = regex.Match(re2::StringPiece(expression.data(), expression.size()), offset, expression.size(), anchor,
                        matches, static_cast<int>(count));

                    if (result.match)
                    {
                        result.matches.reserve(count);

                        for (std::size_t i = 0; i < count; ++i)
                        {
                            const auto& match = count > localMatches.size() ? extraMatches.at(i) : localMatches.at(i);

                            result.matches.emplace_back(match.data() == nullptr ? expression.data() + expression.size() : match.data(),
                                match.size());
                        }
                    }
                }

                template<typename Callback>
                void ForEachMatch(std::string_view expression, const Callback& callback, bool captureGroups = true) const
                {
                    if (expression.data() == nullptr)
                    {
                        expression = "";
                    }

                    std::size_t offset = 0;
                    RegexResult match;

                    while (offset <= expression.size())
                    {
                        MatchAt(expression, offset, re2::RE2::UNANCHORED, captureGroups, match);

                        if (!match.match)
                        {
                            break;
                        }

                        const auto position = static_cast<std::size_t>(match.matches.front().data() - expression.data());

                        callback(match, position);
                        offset = position + match.matches.front().size();

                        if (match.matches.front().empty())
                        {
                            ++offset;

                            if (regex.options().encoding() == re2::RE2::Options::EncodingUTF8)
                            {
                                constexpr unsigned char continuationMask = 0xC0;
                                constexpr unsigned char continuationTag = 0x80;

                                while (offset < expression.size() &&
                                       (static_cast<unsigned char>(expression.at(offset)) & continuationMask) == continuationTag)
                                {
                                    ++offset;
                                }
                            }
                        }
                    }
                }

                re2::RE2 regex;
            };
        }
#endif
    }

    Regex::Regex(std::string_view pattern)
#ifdef CUCUMBER_GHERKIN_HAS_RE2
        : strategy(std::make_shared<detail::Re2RegexStrategy>(pattern))
#else
        : strategy(std::make_shared<detail::StdRegexStrategy>(pattern))
#endif
    {}

    WideRegex::WideRegex(std::wstring_view pattern)
#ifdef CUCUMBER_GHERKIN_HAS_RE2
        : strategy(std::make_shared<detail::Re2RegexStrategy>(ToNarrow(pattern), true))
#else
        : strategy(std::make_shared<detail::StdWideRegexStrategy>(pattern))
#endif
    {}

    std::wstring WideRegex::Replace(std::wstring_view source, std::wstring_view replacement) const
    {
        return strategy->Replace(source, replacement);
    }

    RegexResult Regex::Match(std::string_view expression, bool full) const
    {
        return strategy->Match(expression, full);
    }

    std::string Regex::Replace(std::string_view source, std::string_view replacement) const
    {
        return strategy->Replace(source, replacement);
    }

    Strings Regex::Split(std::string_view expression) const
    {
        return strategy->Split(expression);
    }

    void Split(const std::string& pattern, const std::string& expr, Strings& list)
    {
        list = Split(pattern, expr);
    }

    Strings Split(const std::string& pattern, const std::string& expr)
    {
        return Regex(pattern).Split(expr);
    }

    std::string Substitute(const std::string& source, const std::string& pattern, const std::string& what)
    {
        return Regex(pattern).Replace(source, what);
    }

    void Substitute(std::string& source, const std::string& pattern, const std::string& what)
    {
        source = Substitute(static_cast<const std::string&>(source), pattern, what);
    }

    std::wstring Substitute(const std::wstring& source, const std::wstring& pattern, const std::wstring& what)
    {
        return WideRegex(pattern).Replace(source, what);
    }
}
