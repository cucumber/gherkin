#ifndef CUCUMBER_GHERKIN_PARSER_INFO_HPP
#define CUCUMBER_GHERKIN_PARSER_INFO_HPP

#include <functional>
#include <string>

namespace cucumber::gherkin
{

    using id_generator_func = std::function<std::string()>;

    struct parser_info
    {
        std::string language = "en";
        id_generator_func id_generator;
    };

}

#endif
