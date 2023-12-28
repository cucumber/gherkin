#pragma once

#include <vector>
#include <set>
#include <unordered_set>

namespace cucumber::gherkin {

template <typename T>
struct is_vector : public std::false_type{};

template <typename T>
struct is_vector<std::vector<T>> : public std::true_type{};

template <typename T>
using is_vector_t = typename is_vector<T>::type;

template <typename T>
constexpr bool is_vector_v = is_vector<T>::value;

template <typename T>
struct is_set : public std::false_type{};

template <typename T>
struct is_set<std::set<T>> : public std::true_type{};

template <typename T>
using is_set_t = typename is_set<T>::type;

template <typename T>
constexpr bool is_set_v = is_set<T>::value;

template <typename T>
struct is_unordered_set : public std::false_type{};

template <typename T>
struct is_unordered_set<std::unordered_set<T>> : public std::true_type{};

template <typename T>
using is_unordered_set_t = typename is_unordered_set<T>::type;

template <typename T>
constexpr bool is_unordered_set_v = is_unordered_set<T>::value;

}
