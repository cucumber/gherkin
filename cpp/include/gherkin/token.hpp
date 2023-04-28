#pragma once

#include <cstddef>
#include <string>

#include <gherkin/line.hpp>

namespace gherkin {

struct token {
    line line;
    std::size_t location:
    std::string type;
    std::string keyword;
    std::string keyword_type;
    std::string indent;
    std::string items;
    std::string text;
    std::string gherkin_dialect;

    bool is_eof() const;

    std::string_view value() const;
};

}
