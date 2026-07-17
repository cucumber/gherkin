#ifndef CUCUMBER_GHERKIN_JOIN_UTILS_HPP
#define CUCUMBER_GHERKIN_JOIN_UTILS_HPP

#include "cucumber/gherkin/container_helpers.hpp"
#include <cstddef>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>

namespace cucumber::gherkin
{

    namespace detail
    {

        template<typename Container>
        std::size_t JoinContainerImpl(std::ostream& ostream, const std::string& separator, const Container& container)
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
    struct IsJoinableContainer
    {
        using type = std::conditional_t<isVectorV<T> || isSetV<T> || isUnorderedSetV<T>, std::true_type, std::false_type>;

        static constexpr typename type::value_type value = type::value;
    };

    template<typename T>
    using is_joinable_container_t = typename IsJoinableContainer<T>::type;

    template<typename T>
    constexpr bool isJoinableContainerV = IsJoinableContainer<T>::value;

    template<typename... Args>
    void JoinItemImpl(std::ostream& ostream, const std::string& separator, Args&&... args)
    {
        std::size_t prevCount = 0;

        auto joinArg = [&](auto&& arg)
        {
            using type = std::decay_t<decltype(arg)>;

            if constexpr (isJoinableContainerV<type>)
            {
                if (prevCount && !arg.empty())
                {
                    ostream << separator;
                }

                prevCount += detail::JoinContainerImpl(ostream, separator, arg);
            }
            else
            {
                if (prevCount)
                {
                    ostream << separator;
                }

                ostream << arg;
                ++prevCount;
            }
        };

        (joinArg(std::forward<Args>(args)), ...);
    }

    template<typename... Args>
    std::string Join(const std::string& separator, Args&&... args)
    {
        std::ostringstream stream;

        JoinItemImpl(stream, separator, std::forward<Args>(args)...);

        return stream.str();
    }

}

#endif
