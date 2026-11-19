#ifndef CUCUMBER_GHERKIN_REGEX_HPP
#define CUCUMBER_GHERKIN_REGEX_HPP

#include "cucumber/gherkin/Demangle.hpp"
#include "cucumber/gherkin/Log.hpp"
#include "cucumber/gherkin/Types.hpp"
#include <charconv>
#include <cstddef>
#include <iterator>
#include <memory>
#include <string>
#include <string_view>
#include <system_error>
#include <type_traits>
#include <utility>
#include <vector>

namespace cucumber::gherkin
{

    struct RegexResult
    {
        bool match = false;
        StringViews matches;
    };

    namespace detail
    {
        class RegexStrategy;
        class WideRegexStrategy;
    }

    class Regex
    {
    public:
        explicit Regex(std::string_view pattern);

        [[nodiscard]] RegexResult Match(std::string_view expression, bool full) const;
        [[nodiscard]] std::string Replace(std::string_view source, std::string_view replacement) const;
        [[nodiscard]] Strings Split(std::string_view expression) const;

    private:
        std::shared_ptr<const detail::RegexStrategy> strategy;
    };

    class WideRegex
    {
    public:
        explicit WideRegex(std::wstring_view pattern);

        [[nodiscard]] std::wstring Replace(std::wstring_view source, std::wstring_view replacement) const;

    private:
        std::shared_ptr<const detail::WideRegexStrategy> strategy;
    };

    void Split(const std::string& pattern, const std::string& expr, Strings& list);

    [[nodiscard]] Strings Split(const std::string& pattern, const std::string& expr);

    [[nodiscard]] std::string Substitute(const std::string& source, const std::string& pattern, const std::string& what = {});

    void Substitute(std::string& source, const std::string& pattern, const std::string& what = {});

    [[nodiscard]] std::wstring Substitute(const std::wstring& source, const std::wstring& pattern, const std::wstring& what = {});

    namespace detail
    {

        struct NullArg
        {};

        template<typename CharT, typename SubMatch, typename Arg = NullArg>
        auto ExtractSubmatch(const SubMatch& submatch, Arg&& argument) // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            using ArgType = std::decay_t<Arg>;
            using SvType = std::basic_string_view<CharT>;

            constexpr bool isString =
                std::is_same_v<ArgType, std::basic_string<CharT>> || std::is_same_v<ArgType, std::basic_string_view<CharT>>;

            constexpr bool isNumber = std::is_integral_v<ArgType> || std::is_floating_point_v<ArgType>;

            SvType const view = submatch;

            if constexpr (isString)
            {
                argument = view;
            }
            else if constexpr (isNumber)
            {
                const auto* begin = view.data() == nullptr ? "" : view.data();
                const auto* end = std::next(begin, view.size());

                const auto [ptr, errorCode] = std::from_chars(begin, end, argument);

                DieUnless(errorCode == std::errc(), "failed to convert \"", view, "\" to ", Declname(argument).get());
            }

            return view;
        }

        template<std::size_t N, typename MatchResult>
        void CheckMatchArgs(const MatchResult& matchResult)
        {
            if constexpr (N > 0)
            {
                auto expected = matchResult.size() - 1;

                DieUnless(N == expected, "incorrect match args: ", "expected ", expected, ", got ", N);
            }
        }

        template<typename CharT, typename MatchResult, typename... Args>
        void ExtractSubmatches(const MatchResult& matchResult, Args&&... args)
        {
            constexpr auto nargs = sizeof...(args);

            CheckMatchArgs<nargs>(matchResult);

            auto matchIter = matchResult.begin();

            if constexpr (nargs > 0)
            {
                (ExtractSubmatch<CharT>(*++matchIter, std::forward<Args>(args)), ...);
            }
        }

        template<typename CharT, typename Traits, typename MatchResult>
        void ExtractSubmatches(const MatchResult& matchResult, std::vector<std::basic_string_view<CharT, Traits>>& views)
        {
            auto matchIter = matchResult.begin();

            while (++matchIter != matchResult.end())
            {
                views.push_back(*matchIter);
            }
        }

    }

    template<typename... Args>
    bool FullMatch(std::string_view expression, const Regex& regex, Args&&... args)
    {
        const auto result = regex.Match(expression, true);

        if (result.match)
        {
            detail::ExtractSubmatches<char>(result.matches, std::forward<Args>(args)...);
        }

        return result.match;
    }

    template<typename... Args>
    bool FullMatch(std::string_view expression, std::string_view pat, Args&&... args) // NOLINT(bugprone-easily-swappable-parameters)
    {
        return FullMatch(expression, Regex(pat), std::forward<Args>(args)...);
    }

    template<typename... Args>
    bool PartialMatch(std::string_view expression, const Regex& regex, Args&&... args)
    {
        const auto result = regex.Match(expression, false);

        if (result.match)
        {
            detail::ExtractSubmatches<char>(result.matches, std::forward<Args>(args)...);
        }

        return result.match;
    }

    template<typename... Args>
    bool PartialMatch(std::string_view expression, std::string_view pat, Args&&... args)
    {
        return PartialMatch(expression, Regex(pat), std::forward<Args>(args)...);
    }

}

#endif
