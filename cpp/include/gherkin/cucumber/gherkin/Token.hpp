#ifndef CUCUMBER_GHERKIN_TOKEN_HPP
#define CUCUMBER_GHERKIN_TOKEN_HPP

#include "cucumber/gherkin/Items.hpp"
#include "cucumber/gherkin/Line.hpp"
#include "cucumber/gherkin/RuleType.hpp"
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
        Line line;
        RuleType matchedType = RuleType::none;
        std::optional<std::string> matchedKeyword;
        std::optional<messages::StepKeywordType> matchedKeywordType;
        std::size_t matchedIndent = 0;
        Items matchedItems;
        std::string matchedText;
        std::string matchedGherkinDialect;
        messages::Location location;

        [[nodiscard]] bool IsEof() const;

        [[nodiscard]] std::string_view Value() const;
    };

    using Tokens = std::vector<Token>;
    using TokenQueue = std::deque<Token>;
}

#endif
