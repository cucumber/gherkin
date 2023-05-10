#pragma once

#include <cstddef>
#include <string>
#include <deque>
#include <vector>

#include <cucumber/messages/step_keyword_type.hpp>

#include <gherkin/line.hpp>
#include <gherkin/location.hpp>
#include <gherkin/items.hpp>
#include <gherkin/rule_type.hpp>

namespace gherkin {

struct token
{
    bool eof = false;
    gherkin::line line;
    rule_type matched_type;
    std::string matched_keyword;
    cucumber::messages::step_keyword_type matched_keyword_type;
    std::size_t matched_indent = 0;
    gherkin::items matched_items;
    std::string matched_text;
    std::string matched_gherkin_dialect;
    gherkin::location location;

    bool is_eof() const;

    void detach();

    std::string_view value() const;
};

using tokens = std::vector<token>;
using token_queue = std::deque<token>;

}
