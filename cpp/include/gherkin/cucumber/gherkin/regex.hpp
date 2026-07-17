#ifndef CUCUMBER_GHERKIN_REGEX_HPP
#define CUCUMBER_GHERKIN_REGEX_HPP

#include "cucumber/gherkin/demangle.hpp"
#include "cucumber/gherkin/log.hpp"
#include "cucumber/gherkin/types.hpp"
#include <charconv>
#include <cstddef>
#include <regex>
#include <string>
#include <string_view>
#include <system_error>
#include <type_traits>
#include <vector>

namespace cucumber::gherkin
{

    struct RegexResult
    {
        bool match = false;
        StringViews matches;
    };

    void Split(const std::string& pattern, const std::string& expr, Strings& list);

    Strings Split(const std::string& pattern, const std::string& expr);

    std::string Subst(const std::string& source, const std::string& pattern, const std::string& what = {});

    void Subst(std::string& source, const std::string& pattern, const std::string& what = {});

    namespace detail
    {

        struct NullArg
        {};

        template<typename CharT, typename SubMatch, typename Arg = NullArg>
        auto ExtractSubmatch(const SubMatch& submatch, Arg&& argument) // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            using ArgType = std::decay_t<Arg>;
            using SvType = std::basic_string_view<CharT>;

            constexpr bool isString = std::is_same_v<ArgType, std::basic_string<CharT>> || std::is_same_v<ArgType, std::basic_string_view<CharT>>;

            constexpr bool isNumber = std::is_integral_v<ArgType> || std::is_floating_point_v<ArgType>;

            SvType const view{ submatch.first, static_cast<std::size_t>(submatch.length()) };

            if constexpr (isString)
            {
                argument.assign(view);
            }
            else if constexpr (isNumber)
            {
                auto [ptr, error_code] = std::from_chars(view.begin(), view.end(), argument);

                DieUnless(error_code == std::errc(), "failed to convert \"", view, "\" to ", Declname(argument));
            }
            else if constexpr (!std::is_same_v<ArgType, NullArg>)
            {
                die("unsupported argument: ", Declname(argument));
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
                views.push_back(std::basic_string_view<CharT, Traits>{ matchIter->first, matchIter->second });
            }
        }

    }

    template<typename CharT, typename Traits, typename ReTraits, typename... Args>
    bool FullMatch(std::basic_string_view<CharT, Traits> expression, const std::basic_regex<CharT, ReTraits>& regex, Args&&... args)
    {
        std::match_results<const CharT*> matchResult;
        auto beginPtr = expression.data();
        auto endPtr = expression.data() + expression.size();

        bool const match = std::regex_match(beginPtr, endPtr, matchResult, regex);

        if (match)
        {
            detail::ExtractSubmatches<CharT>(matchResult, std::forward<Args>(args)...);
        }

        return match;
    }

    template<typename CharT, typename Traits, typename... Args>
    bool FullMatch(std::basic_string_view<CharT, Traits> expression, std::basic_string_view<CharT, Traits> pat, Args&&... args) // NOLINT(bugprone-easily-swappable-parameters)
    {
        std::basic_regex<CharT> regex(pat.data(), pat.size());

        return full_match(expression, regex, std::forward<Args>(args)...);
    }

    template<typename CharT, typename Traits, typename Allocator, typename... Args>
    bool FullMatch(const std::basic_string<CharT, Traits, Allocator>& expression, Args&&... args)
    {
        return FullMatch(std::basic_string_view<CharT, Traits>{ expression.data(), expression.size() }, std::forward<Args>(args)...);
    }

    template<typename CharT, typename Traits, typename... Args>
    bool PartialMatch(std::basic_string_view<CharT, Traits> expression, std::basic_string_view<CharT, Traits> pat, Args&&... args) // NOLINT(bugprone-easily-swappable-parameters)
    {
        std::match_results<const CharT*> matchResult;
        std::regex regex(pat.data(), pat.size());

        bool match = std::regex_search(expression.begin(), expression.end(), matchResult, regex);

        if (match)
        {
            detail::ExtractSubmatches(matchResult, std::forward<Args>(args)...);
        }

        return match;
    }

}

#endif
