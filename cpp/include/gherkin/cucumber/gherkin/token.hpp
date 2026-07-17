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
#include <string_view>
#include <vector>

namespace cucumber::gherkin
{
    struct Token
    {
        bool eof = false;
        cucumber::gherkin::Line line;
        RuleType matchedType = RuleType::none;
        std::optional<std::string> matchedKeyword;
        std::optional<cucumber::messages::StepKeywordType> matchedKeywordType;
        std::size_t matchedIndent = 0;
        cucumber::gherkin::items matchedItems;
        std::string matchedText;
        std::string matchedGherkinDialect;
        cucumber::messages::Location location;

        [[nodiscard]] bool IsEof() const;

        void Detach();

        [[nodiscard]] std::string_view Value() const;
    };

    using tokens = std::vector<Token>;
    using token_queue = std::deque<Token>;

}

#endif
