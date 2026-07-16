#pragma once

#include "cucumber/gherkin/demangle.hpp"
#include "cucumber/gherkin/log.hpp"
#include "cucumber/gherkin/types.hpp"
#include "cucumber/gherkin/utils.hpp"
#include <charconv>
#include <regex>

namespace cucumber::gherkin
{

    struct regex_result
    {
        bool match = false;
        string_views matches;
    };

    void split(const std::string& pattern, const std::string& expr, strings& list);

    strings split(const std::string& pattern, const std::string& expr);

    std::string subst(const std::string& source, const std::string& pattern, const std::string& what = {});

    void subst(std::string& source, const std::string& pattern, const std::string& what = {});

    namespace detail
    {

        struct null_arg
        {};

        template<typename CharT, typename SubMatch, typename Arg = null_arg>
        auto extract_submatch(const SubMatch& submatch, Arg&& argument)
        {
            using arg_type = std::decay_t<Arg>;
            using sv_type = std::basic_string_view<CharT>;

            constexpr bool is_string = std::is_same_v<arg_type, std::basic_string<CharT>> || std::is_same_v<arg_type, std::basic_string_view<CharT>>;

            constexpr bool is_number = std::is_integral_v<arg_type> || std::is_floating_point_v<arg_type>;

            sv_type view{ submatch.first, static_cast<std::size_t>(submatch.length()) };

            if constexpr (is_string)
            {
                argument.assign(view);
            }
            else if constexpr (is_number)
            {
                auto [ptr, error_code] = std::from_chars(view.begin(), view.end(), argument);

                die_unless(error_code == std::errc(), "failed to convert \"", view, "\" to ", declname(argument));
            }
            else if constexpr (!std::is_same_v<arg_type, null_arg>)
            {
                die("unsupported argument: ", declname(argument));
            }

            return view;
        }

        template<std::size_t N, typename MatchResult>
        void check_match_args(MatchResult&& match_result)
        {
            if constexpr (N > 0)
            {
                auto expected = match_result.size() - 1;

                die_unless(N == expected, "incorrect match args: ", "expected ", expected, ", got ", N);
            }
        }

        template<typename CharT, typename MatchResult, typename... Args>
        void extract_submatches(MatchResult&& match_result, Args&&... args)
        {
            constexpr auto nargs = sizeof...(args);

            check_match_args<nargs>(match_result);

            auto match_iter = match_result.begin();

            if constexpr (nargs > 0)
            {
                (extract_submatch<CharT>(*++match_iter, std::forward<Args>(args)), ...);
            }
        }

        template<typename CharT, typename Traits, typename MatchResult>
        void extract_submatches(MatchResult&& match_result, std::vector<std::basic_string_view<CharT, Traits>>& views)
        {
            auto match_iter = match_result.begin();

            while (++match_iter != match_result.end())
            {
                views.push_back(std::basic_string_view<CharT, Traits>{ match_iter->first, match_iter->second });
            }
        }

    }

    template<typename CharT, typename Traits, typename ReTraits, typename... Args>
    bool full_match(std::basic_string_view<CharT, Traits> expression, const std::basic_regex<CharT, ReTraits>& regex, Args&&... args)
    {
        std::match_results<const CharT*> match_result;
        auto begin_ptr = expression.data();
        auto end_ptr = expression.data() + expression.size();

        bool match = std::regex_match(begin_ptr, end_ptr, match_result, regex);

        if (match)
        {
            detail::extract_submatches<CharT>(match_result, std::forward<Args>(args)...);
        }

        return match;
    }

    template<typename CharT, typename Traits, typename... Args>
    bool full_match(std::basic_string_view<CharT, Traits> expression, std::basic_string_view<CharT, Traits> pat, Args&&... args)
    {
        std::basic_regex<CharT> regex(pat.data(), pat.size());

        return full_match(expression, regex, std::forward<Args>(args)...);
    }

    template<typename CharT, typename Traits, typename Allocator, typename... Args>
    bool full_match(const std::basic_string<CharT, Traits, Allocator>& expression, Args&&... args)
    {
        return full_match(std::basic_string_view<CharT, Traits>{ expression.data(), expression.size() }, std::forward<Args>(args)...);
    }

    template<typename CharT, typename Traits, typename... Args>
    bool partial_match(std::basic_string_view<CharT, Traits> expression, std::basic_string_view<CharT, Traits> pat, Args&&... args)
    {
        std::match_results<const CharT*> match_result;
        std::regex regex(pat.data(), pat.size());

        bool match = std::regex_search(expression.begin(), expression.end(), match_result, regex);

        if (match)
        {
            detail::extract_submatches(match_result, std::forward<Args>(args)...);
        }

        return match;
    }

}
