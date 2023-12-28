#pragma once

#include <sstream>
#include <type_traits>

#include <cucumber/gherkin/container_helpers.hpp>

namespace cucumber::gherkin {

namespace detail {

template <typename Container>
std::size_t
join_container_impl(
    std::ostream& os,
    const std::string& sep,
    const Container& c
)
{
    if (!c.empty()) {
        auto it = c.begin();

        os << *it;

        while (++it != c.end()) {
            os << sep << *it;
        }
    }

    return c.size();
}

} // namespace detail

template <typename T>
struct is_joinable_container
{
    using type = std::conditional_t<
        is_vector_v<T>
        || is_set_v<T>
        || is_unordered_set_v<T>,
        std::true_type,
        std::false_type
    >;

    static constexpr typename type::value_type value = type::value;
};

template <typename T>
using is_joinable_container_t = typename is_joinable_container<T>::type;

template <typename T>
constexpr bool is_joinable_container_v = is_joinable_container<T>::value;

template <typename... Args>
void
join_item_impl(
    std::ostream& os,
    const std::string& sep,
    Args&&... args
)
{
    std::size_t prev_count = 0;

    auto join_arg = [&](auto&& arg) {
        using type = std::decay_t<decltype(arg)>;

        if constexpr (is_joinable_container_v<type>) {
            if (prev_count && !arg.empty()) {
                os << sep;
            }

            prev_count += detail::join_container_impl(os, sep, arg);
        } else {
            if (prev_count) {
                os << sep;
            }

            os << arg;
            ++prev_count;
        }
    };

    (join_arg(std::forward<Args>(args)), ...);
}

template <typename... Args>
std::string
join(const std::string& sep, Args&&... args)
{
    std::ostringstream oss;

    join_item_impl(oss, sep, std::forward<Args>(args)...);

    return oss.str();
}

}
