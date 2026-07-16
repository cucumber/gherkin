#ifndef CUCUMBER_GHERKIN_TOKEN_HPP
#define CUCUMBER_GHERKIN_TOKEN_HPP

#include "cucumber/gherkin/items.hpp"
#include "cucumber/gherkin/line.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/messages/Location.hpp"
#include "cucumber/messages/StepKeywordType.hpp"
#include <cstddef>
#include <deque>
#include <optional>
#include <string>
#include <vector>

namespace cucumber::gherkin
{

    namespace cms = cucumber::messages;

    struct Token
    {
        bool eof = false;
        cucumber::gherkin::Line line;
        RuleType matched_type;
        std::optional<std::string> matched_keyword;
        std::optional<cms::StepKeywordType> matched_keyword_type;
        std::size_t matched_indent = 0;
        cucumber::gherkin::items matched_items;
        std::string matched_text;
        std::string matched_gherkin_dialect;
        cms::Location location;

        bool is_eof() const;

        void detach();

        std::string_view value() const;
    };

    using tokens = std::vector<Token>;
    using token_queue = std::deque<Token>;

}

#endif
