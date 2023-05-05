#pragma once

#include <cstddef>
#include <string>
#include <deque>

#include <gherkin/line.hpp>
#include <gherkin/items.hpp>

namespace gherkin {

struct token
{
    gherkin::line line;
    std::size_t location;
    std::string matched_type;
    std::string matched_keyword;
    std::string matched_keyword_type;
    std::size_t matched_indent = 0;
    gherkin::items matched_items;
    std::string matched_text;
    std::string matched_gherkin_dialect;

    bool is_eof() const;

    void detach();

    std::string_view value() const;
};

using token_queue = std::deque<token>;

}
