#ifndef CUCUMBER_GHERKIN_DEMANGLE_HPP
#define CUCUMBER_GHERKIN_DEMANGLE_HPP

#include <memory>
#include <string>

namespace cucumber::gherkin
{

    namespace detail
    {

        auto Demangle(const std::string& name) -> std::unique_ptr<char, void (*)(char*)>;
    }

    template<typename T>
    auto Declname()
    {
        return detail::Demangle(typeid(T).name());
    }

    template<typename T>
    auto Declname([[maybe_unused]] T&& /*value*/) // NOLINT(cppcoreguidelines-missing-std-forward)
    {
        return Declname<T>();
    }

}

#endif
