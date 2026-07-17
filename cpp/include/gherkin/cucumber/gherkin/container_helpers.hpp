#ifndef CUCUMBER_GHERKIN_CONTAINER_HELPERS_HPP
#define CUCUMBER_GHERKIN_CONTAINER_HELPERS_HPP

#include <set>
#include <unordered_set>
#include <vector>

namespace cucumber::gherkin
{

    template<typename T>
    struct IsVector : public std::false_type
    {};

    template<typename T>
    struct IsVector<std::vector<T>> : public std::true_type
    {};

    template<typename T>
    using is_vector_t = typename IsVector<T>::type;

    template<typename T>
    constexpr bool isVectorV = IsVector<T>::value;

    template<typename T>
    struct IsSet : public std::false_type
    {};

    template<typename T>
    struct IsSet<std::set<T>> : public std::true_type
    {};

    template<typename T>
    using is_set_t = typename IsSet<T>::type;

    template<typename T>
    constexpr bool isSetV = IsSet<T>::value;

    template<typename T>
    struct IsUnorderedSet : public std::false_type
    {};

    template<typename T>
    struct IsUnorderedSet<std::unordered_set<T>> : public std::true_type
    {};

    template<typename T>
    using is_unordered_set_t = typename IsUnorderedSet<T>::type;

    template<typename T>
    constexpr bool isUnorderedSetV = IsUnorderedSet<T>::value;
}

#endif
