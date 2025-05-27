// https://gist.github.com/bwoods/bbc6bd26b73fa37e94ac

#if defined(_MSC_VER)
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
#else
#include <cxxabi.h> // gcc and clang…
#endif

#include <stdlib.h>

#include <cucumber/gherkin/demangle.hpp>

namespace cucumber::gherkin {

namespace detail {

auto
demangle(std::string&& name)
-> std::unique_ptr<char, void(*)(char *)>
{
    int status = 0;

#if defined(_MSC_VER)
    //try to allocate a buffer as __cxa_demangle will do
    //assuming symbol name is less than 1024 bytes
    char* realname = (char*) malloc(1024 * sizeof(char));

    if (realname) {
        ::UnDecorateSymbolName(name.c_str(), realname, 1024, 0);
    }

    return { realname, [] (char * p) { ::free(p); } };
#else
    return
        {
            abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status),
            [] (char * p) { ::free(p); }
        };
#endif
}

} // namespace detail

}
