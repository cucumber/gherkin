// https://gist.github.com/bwoods/bbc6bd26b73fa37e94ac

#include <cxxabi.h> // gcc and clang…
#include <stdlib.h>

#include <cucumber/gherkin/demangle.hpp>

namespace cucumber::gherkin {

namespace detail {

auto
demangle(std::string&& name)
-> std::unique_ptr<char, void(*)(char *)>
{
    int status = 0;

    return
        {
            abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status),
            [] (char * p) { ::free(p); }
        };
}

} // namespace detail

}
