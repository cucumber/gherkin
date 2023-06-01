#pragma once

#include <cstddef>
#include <string>
#include <deque>
#include <vector>
#include <optional>

#include <cucumber/messages/location.hpp>
#include <cucumber/messages/step_keyword_type.hpp>

#include <gherkin/line.hpp>
#include <gherkin/items.hpp>
#include <gherkin/generated/rule_type.hpp>

namespace gherkin {

namespace cms = cucumber::messages;

struct token
{
    bool eof = false;
    gherkin::line line;
    rule_type matched_type;
    std::optional<std::string> matched_keyword;
    std::optional<cms::step_keyword_type> matched_keyword_type;
    std::size_t matched_indent = 0;
    gherkin::items matched_items;
    std::string matched_text;
    std::string matched_gherkin_dialect;
    cms::location location;

    bool is_eof() const;

    void detach();

    std::string_view value() const;
};

using tokens = std::vector<token>;
using token_queue = std::deque<token>;

}
