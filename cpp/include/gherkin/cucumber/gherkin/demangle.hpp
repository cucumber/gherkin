#pragma once

#include <memory>
#include <string>

namespace cucumber::gherkin {

namespace detail {

auto
demangle(std::string&& name)
-> std::unique_ptr<char, void(*)(char *)>;

}

template <typename T>
auto declname()
{ return detail::demangle(typeid(T).name()); }

template <typename T>
auto declname(T&& v)
{ return declname<T>(); }

}
