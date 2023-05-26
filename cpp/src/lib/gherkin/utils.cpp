#include <clocale>
#include <cwchar>
#include <fstream>
#include <filesystem>
#include <string_view>
#include <regex>

#include <gherkin/utils.hpp>

namespace gherkin {

std::string_view
spaces_pattern()
{ return { "[ \\t\\n\\v\\f\\r\\u0085\\u00A0]+" }; }

std::string_view
spaces_no_nl_pattern()
{ return { "[ \\t\\v\\f\\r\\u0085\\u00A0]+" }; }

std::size_t
codepoint_count(std::string_view s)
{
    std::size_t count = 0;
    std::mbstate_t mb = std::mbstate_t();
    auto data = s.data();
    auto size = s.size();

    for (std::size_t i = 0; i < size; ) {
        int l = std::mbrlen(&data[i], size - i, &mb);

        if (l == -2) {
            // Incomplete character
            l = std::mbrlen(&data[i + 1], size - i - 1, &mb);

            if (l > 0) {
                count += l;
                i += l;
            }
        } else {
            ++count;
            ++i;
        }
    }

    return count;
}

std::string
strip_pattern::str() const
{
    std::string s(prefix.size() + chars.size() + suffix.size(), ' ');

    s = prefix;
    s += chars;
    s += suffix;

    return s;
}

std::string
strip(std::string_view what, const strip_pattern& p)
{
    auto pat = p.str();
    std::regex re(pat);
    std::string empty;
    std::string result;

    std::regex_replace(
        std::back_inserter(result),
        what.begin(), what.end(),
        re,
        empty
    );

    return result;
}

std::string
lstrip(std::string_view in, std::string_view chars)
{ return strip(in, strip_pattern{ .prefix = "^", .chars = chars }); }

std::string
rstrip(std::string_view in, std::string_view chars)
{ return strip(in, strip_pattern{ .chars = chars, .suffix = "$" }); }

std::string
strip(std::string_view in, std::string_view chars)
{ return lstrip(rstrip(in, chars), chars); }

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
