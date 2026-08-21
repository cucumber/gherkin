#ifndef CUCUMBER_GHERKIN_JOIN_UTILS_HPP
#define CUCUMBER_GHERKIN_JOIN_UTILS_HPP

#include <sstream>
#include <string>

namespace cucumber::gherkin
{
    template<typename T>
    std::string Join(const std::string& separator, const T& arg)
    {
        std::ostringstream stream;

        if (!arg.empty())
        {
            stream << arg.front();

            for (auto current = std::next(arg.begin()); current != arg.end(); ++current)
            {
                stream << separator << *current;
            }
        }

        return stream.str();
    }

}

#endif
