#ifndef CUCUMBER_GHERKIN_TOKEN_MATCHER_HPP
#define CUCUMBER_GHERKIN_TOKEN_MATCHER_HPP

#include "cucumber/gherkin/items.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/types.hpp"
#include "cucumber/messages/StepKeywordType.hpp"
#include <cstddef>
#include <cucumber/messages/Location.hpp>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace cucumber::gherkin
{

    using KeywordTypes = std::vector<messages::StepKeywordType>;
    using KeywordTypesMap = std::unordered_map<std::string_view, KeywordTypes>;

    class TokenMatcher
    {
    public:
        TokenMatcher(const std::string& dialectName = "en");
        virtual ~TokenMatcher() = default;
        TokenMatcher(const TokenMatcher&) = delete;
        TokenMatcher& operator=(const TokenMatcher&) = delete;
        TokenMatcher(TokenMatcher&&) = delete;
        TokenMatcher& operator=(TokenMatcher&&) = delete;

        void Reset();

        bool MatchFeatureLine(Token& token);
        bool MatchRuleLine(Token& token);
        bool MatchScenarioLine(Token& token);
        bool MatchBackgroundLine(Token& token);
        bool MatchExamplesLine(Token& token);
        bool MatchLanguage(Token& token);
        bool MatchTagLine(Token& token);
        bool MatchEOF(Token& token);
        bool MatchEmpty(Token& token);
        bool MatchComment(Token& token);
        bool MatchOther(Token& token);
        bool MatchStepLine(Token& token);
        bool MatchDocStringSeparator(Token& token);
        bool MatchTableRow(Token& token);

    private:
        bool MatchDocStringSeparator(Token& token, std::string_view separator, bool isOpen);

        bool MatchTitleLine(Token& token, RuleType tokenType, const StringViews& keywords);

        struct TokenInfo
        {
            std::optional<std::string> text;
            std::optional<std::string> keyword;
            std::optional<messages::StepKeywordType> keywordType;
            std::optional<std::size_t> indent;
            Items items;
        };

        void SetTokenMatched(Token& token, RuleType matchedType, const TokenInfo& info = {});

        [[nodiscard]] const StringViews& Keywords(std::string_view keyword) const;

        [[nodiscard]] messages::StepKeywordType KeywordType(std::string_view keyword) const;

        void ChangeDialect(const std::string& dialectName, const messages::Location& location = { 1, 1 });

        [[nodiscard]] std::string UnescapeDocstring(const std::string& text) const;

        std::string dialectName;
        KeywordTypesMap keywordTypes;
        std::string activeDocStringSeparator;
        std::size_t indentToRemove = 0;
    };

}

#endif
