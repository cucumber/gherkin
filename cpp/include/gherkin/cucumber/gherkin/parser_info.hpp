#ifndef CUCUMBER_GHERKIN_PARSER_INFO_HPP
#define CUCUMBER_GHERKIN_PARSER_INFO_HPP

#include <functional>
#include <string>

namespace cucumber::gherkin
{

    using IdGeneratorFunc = std::function<std::string()>;

    struct ParserInfo
    {
        std::string language = "en";
        IdGeneratorFunc IdGenerator;
    };

}

#endif
