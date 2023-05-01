#pragma once

#include <cstddef>
#include <string>
#include <deque>

#include <gherkin/line.hpp>

namespace gherkin {

struct token
{
    gherkin::line line;
    std::size_t location;

    bool is_eof() const;

    void detach();

    std::string_view value() const;
};

using token_queue = std::deque<token>;

}
