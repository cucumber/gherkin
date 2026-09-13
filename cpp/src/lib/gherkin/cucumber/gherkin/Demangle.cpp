// https://gist.github.com/bwoods/bbc6bd26b73fa37e94ac

#if defined(_MSC_VER)
// clang-format off
#include <windows.h>  // must come before dbghelp.h
#include <dbghelp.h>
// clang-format on
#pragma comment(lib, "dbghelp.lib")
#else
#include <cxxabi.h> // gcc and clang…
#endif

#include "cucumber/gherkin/Demangle.hpp"
#include <cstdlib>
#include <memory>
#include <string>

namespace cucumber::gherkin::detail
{

    auto Demangle(const std::string& name) -> std::unique_ptr<char, void (*)(char*)>
    {
        int status = 0;

#if defined(_MSC_VER)
        //try to allocate a buffer as __cxa_demangle will do
        //assuming symbol name is less than 1024 bytes
        // NOLINTBEGIN(cppcoreguidelines-no-malloc,cppcoreguidelines-owning-memory)
        auto* realname = static_cast<char*>(malloc(1024 * sizeof(char)));
        // NOLINTEND(cppcoreguidelines-no-malloc,cppcoreguidelines-owning-memory)

        if (realname)
        {
            ::UnDecorateSymbolName(name.c_str(), realname, 1024, 0);
        }

        return { realname, [](char* ptr)
            {
                ::free(ptr); // NOLINT(cppcoreguidelines-no-malloc,cppcoreguidelines-owning-memory)
            } };
#else
        // NOLINTBEGIN(cppcoreguidelines-no-malloc,cppcoreguidelines-owning-memory)
        return { abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status), [](char* ptr)
            {
                ::free(ptr); // NOLINT(cppcoreguidelines-no-malloc,cppcoreguidelines-owning-memory)
            } };
        // NOLINTEND(cppcoreguidelines-no-malloc,cppcoreguidelines-owning-memory)
#endif
    }

}
