#include "cucumber/gherkin/Utils.hpp"
#include <cwchar>
#include <filesystem>
#include <fstream>
#include <ios>
#include <string>
#include <string_view>

namespace cucumber::gherkin
{

    std::string Slurp(const std::string& path)
    {
        namespace fs = std::filesystem;

        std::string bytes;
        std::ifstream ifs(path, std::ios::binary);

        if (ifs.is_open())
        {
            auto fsize = fs::file_size(fs::path{ path });

            bytes.resize(fsize);

            ifs.read(bytes.data(), static_cast<std::streamsize>(fsize));
            ifs.close();
        }

        return bytes;
    }

    void Replace(std::string& source, std::string_view what, std::string_view with)
    {
        std::string::size_type pos = std::string::npos;

        while ((pos = source.find(what)) != std::string::npos)
        {
            source.replace(pos, what.size(), with);
        }
    }

    std::string Replace(const std::string& source, std::string_view what, std::string_view with)
    {
        std::string text = source;

        Replace(text, what, with);

        return text;
    }

}
