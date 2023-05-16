#pragma once

#include <string>

namespace gherkin {

struct parser_info
{
    std::string language = "en";
    bool source_events = true;
    bool ast_events = true;
    bool pickle_events = true;
};

}
