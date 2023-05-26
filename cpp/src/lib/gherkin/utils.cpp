#include <cwchar>
#include <fstream>
#include <filesystem>
#include <string_view>
#include <regex>

#include <gherkin/utils.hpp>

namespace gherkin {

template <typename To, typename From, typename Conv>
auto
mb_conv_core(From&& from, Conv&& c)
{
    using result_type = std::remove_cvref_t<To>;

    result_type res;
    std::mbstate_t state = std::mbstate_t();
    auto from_data = from.data();

    std::size_t len = c(nullptr, &from_data, 0, &state);

    res.resize(len);

    auto res_data = res.data();

    int rc = c(&res_data[0], &from_data, len, &state);

    if (rc < 0) {
        res.clear();
    }

    return res;
}

std::wstring
to_wstring(const std::string& s)
{ return mb_conv_core<std::wstring>(s, std::mbsrtowcs); }

std::string
to_string(const std::wstring& s)
{ return mb_conv_core<std::string>(s, std::wcsrtombs); }

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
