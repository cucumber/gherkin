#include <cwchar>
#include <locale>
#include <fstream>
#include <filesystem>
#include <string_view>
#include <regex>

#include <cucumber/gherkin/utils.hpp>

namespace cucumber::gherkin {

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

void
replace(std::string& s, std::string_view what, std::string_view with)
{
    std::string::size_type pos;

    while ((pos = s.find(what)) != std::string::npos) {
        s.replace(pos, what.size(), with);
    }
}

std::string
replace(const std::string& s, std::string_view what, std::string_view with)
{
    std::string t = s;

    replace(t, what, with);

    return t;
}

}
