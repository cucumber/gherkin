#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <fstream>
#include <filesystem>
#include <string_view>

namespace gherkin {

std::size_t
unicode_size(std::string_view s)
{
    std::mblen(nullptr, 0); // reset the conversion state

    std::size_t result = 0;
    const char* ptr = s.data();

    for (const char* const end = ptr + s.size(); ptr < end; ++result) {
        const int next = std::mblen(ptr, end - ptr);

        if (next == -1) {
            throw std::runtime_error("strlen_mb(): conversion error");
        }

        ptr += next;
    }

    return result;
}

std::string
slurp(const std::string& path)
{
    namespace fs = std::filesystem;

    std::string bytes;
    std::ifstream ifs(path, std::ios::binary);

    if (ifs.is_open()) {
        auto fsize = fs::file_size(fs::path{ path });

        bytes.resize(fsize);

        ifs.read(bytes.data(), fsize);
        ifs.close();
    }

    return bytes;
}

}
