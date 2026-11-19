#include <type_traits>

namespace cucumber::gherkin
{

    template<typename T, template<typename...> typename Primary>
    struct IsSpecializationOf : std::false_type
    {};

    template<template<typename...> typename Primary, typename... Args>
    struct IsSpecializationOf<Primary<Args...>, Primary> : std::true_type
    {};

    template<typename T, template<typename...> class Primary>
    using IsSpecializationOfT = IsSpecializationOf<T, Primary>;

    template<typename T, template<typename...> class Primary>
    inline constexpr bool isSpecializationOfV = IsSpecializationOfT<T, Primary>::value;
}
