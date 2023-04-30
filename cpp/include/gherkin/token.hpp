#pragma once

#include <cstddef>
#include <string>
#include <deque>

#include <gherkin/line.hpp>

namespace gherkin {

struct token
{
    line line;
    std::size_t location:

    bool is_eof() const;

    std::string_view value() const;
};

using token_queue = std::deque<token>;

}
