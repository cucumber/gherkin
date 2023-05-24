#include <fstream>
#include <filesystem>

namespace gherkin {

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
