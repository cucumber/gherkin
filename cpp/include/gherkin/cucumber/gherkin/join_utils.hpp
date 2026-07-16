#ifndef CUCUMBER_GHERKIN_JOIN_UTILS_HPP
#define CUCUMBER_GHERKIN_JOIN_UTILS_HPP

#include "cucumber/gherkin/container_helpers.hpp"
#include <sstream>
#include <type_traits>

namespace cucumber::gherkin
{

    namespace detail
    {

        template<typename Container>
        std::size_t join_container_impl(std::ostream& ostream, const std::string& separator, const Container& container)
        {
            if (!container.empty())
            {
                auto current = container.begin();

                ostream << *current;

                while (++current != container.end())
                {
                    ostream << separator << *current;
                }
            }

            return container.size();
        }

    }

    template<typename T>
    struct is_joinable_container
    {
        using type = std::conditional_t<is_vector_v<T> || is_set_v<T> || is_unordered_set_v<T>, std::true_type, std::false_type>;

        static constexpr typename type::value_type value = type::value;
    };

    template<typename T>
    using is_joinable_container_t = typename is_joinable_container<T>::type;

    template<typename T>
    constexpr bool is_joinable_container_v = is_joinable_container<T>::value;

    template<typename... Args>
    void join_item_impl(std::ostream& ostream, const std::string& separator, Args&&... args)
    {
        std::size_t prev_count = 0;

        auto join_arg = [&](auto&& arg)
        {
            using type = std::decay_t<decltype(arg)>;

            if constexpr (is_joinable_container_v<type>)
            {
                if (prev_count && !arg.empty())
                {
                    ostream << separator;
                }

                prev_count += detail::join_container_impl(ostream, separator, arg);
            }
            else
            {
                if (prev_count)
                {
                    ostream << separator;
                }

                ostream << arg;
                ++prev_count;
            }
        };

        (join_arg(std::forward<Args>(args)), ...);
    }

    template<typename... Args>
    std::string join(const std::string& separator, Args&&... args)
    {
        std::ostringstream stream;

        join_item_impl(stream, separator, std::forward<Args>(args)...);

        return stream.str();
    }

}

#endif
