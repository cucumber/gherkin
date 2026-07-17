
#include "cucumber/gherkin/token_matcher.hpp"
#include "cucumber/gherkin/dialect.hpp"
#include "cucumber/gherkin/exceptions.hpp"
#include "cucumber/gherkin/keywords.hpp"
#include "cucumber/gherkin/regex.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/types.hpp"
#include "cucumber/gherkin/utils.hpp"
#include "cucumber/messages/StepKeywordType.hpp"
#include <algorithm>
#include <cucumber/messages/Location.hpp>
#include <optional>
#include <regex>
#include <string>
#include <string_view>
#include <utility>

namespace cucumber::gherkin
{

    static const std::regex languageRe{ R"(^\s*#\s*language\s*:\s*([a-zA-Z\-_]+)\s*$)" };

    TokenMatcher::TokenMatcher(const std::string& dialectName)
    {
        ChangeDialect(dialectName);
    }

    void TokenMatcher::Reset()
    {
        indentToRemove = 0;
        activeDocStringSeparator.clear();
    }

    bool TokenMatcher::MatchFeatureLine(Token& token)
    {
        return MatchTitleLine(token, RuleType::featureLine, Keywords("feature"));
    }

    bool TokenMatcher::MatchRuleLine(Token& token)
    {
        return MatchTitleLine(token, RuleType::ruleLine, Keywords("rule"));
    }

    bool TokenMatcher::MatchScenarioLine(Token& token)
    {
        auto scenarioType = RuleType::scenarioLine;

        return MatchTitleLine(token, scenarioType, Keywords("scenario")) || MatchTitleLine(token, scenarioType, Keywords("scenarioOutline"));
    }

    bool TokenMatcher::MatchBackgroundLine(Token& token)
    {
        return MatchTitleLine(token, RuleType::backgroundLine, Keywords("background"));
    }

    bool TokenMatcher::MatchExamplesLine(Token& token)
    {
        return MatchTitleLine(token, RuleType::examplesLine, Keywords("examples"));
    }

    bool TokenMatcher::MatchTableRow(Token& token)
    {
        if (!token.line.Startswith("|"))
        {
            return false;
        }

        TokenInfo info;
        info.items = token.line.TableCells();
        SetTokenMatched(token, RuleType::tableRow, info);

        return true;
    }

    bool TokenMatcher::MatchLanguage(Token& token)
    {
        std::string dialectName;

        if (!FullMatch(token.line.LineText(), languageRe, dialectName))
        {
            return false;
        }

        SetTokenMatched(token, RuleType::language, { dialectName });
        ChangeDialect(dialectName);

        return true;
    }

    bool TokenMatcher::MatchTagLine(Token& token)
    {
        if (!token.line.Startswith("@"))
        {
            return false;
        }

        SetTokenMatched(token, RuleType::tagLine, { std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::move(token.line.Tags()) });

        return true;
    }

    bool TokenMatcher::MatchTitleLine(Token& token, RuleType tokenType, const StringViews& keywords)
    {
        for (const auto& keyword : keywords)
        {
            std::string keywordStr(keyword);

            if (!token.line.StartswithTitleKeyword(keywordStr))
            {
                continue;
            }

            SetTokenMatched(token, tokenType, { token.line.GetKeywordTrimmed(keywordStr), keywordStr });

            return true;
        }

        return false;
    }

    bool TokenMatcher::MatchEOF(Token& token)
    {
        if (!token.eof)
        {
            return false;
        }

        SetTokenMatched(token, RuleType::eOF);

        return true;
    }

    bool TokenMatcher::MatchEmpty(Token& token)
    {
        if (!token.line.IsEmpty())
        {
            return false;
        }

        SetTokenMatched(token, RuleType::empty, { std::nullopt, std::nullopt, std::nullopt, 0 });

        return true;
    }

    bool TokenMatcher::MatchComment(Token& token)
    {
        if (!token.line.Startswith("#"))
        {
            return false;
        }

        auto commentText = std::string(token.line.GetLineText(0));

        Substitute(commentText, "[\\r\\n]+$");

        SetTokenMatched(token, RuleType::comment, { commentText, std::nullopt, std::nullopt, 0 });

        return true;
    }

    bool TokenMatcher::MatchOther(Token& token)
    {
        std::string const text = std::string(token.line.GetLineText(indentToRemove));

        SetTokenMatched(token, RuleType::other, { UnescapeDocstring(text), std::nullopt, std::nullopt, 0 });

        return true;
    }

    bool TokenMatcher::MatchStepLine(Token& token)
    {
        StringViews const stepKeywordNames = { "given", "when", "then", "and", "but" };
        auto keywords = cucumber::gherkin::Keywords(dialectName, stepKeywordNames);

        // Prefer the longest step keyword by sorting keywords in descending order
        // by length (in bytes, not codepoints or graphemes - adequate for dealing
        // with keywords that are prefixes of each other).
        std::sort(keywords.begin(), keywords.end(),
            [](const std::string_view& first, const std::string_view& second)
            {
                return first.length() > second.length();
            });

        for (const auto& keyword : keywords)
        {
            if (!token.line.Startswith(keyword))
            {
                continue;
            }

            auto title = token.line.GetRestTrimmed(keyword.size());

            SetTokenMatched(token, RuleType::stepLine, { title, std::string(keyword), KeywordType(keyword) });

            return true;
        }

        return false;
    }

    bool TokenMatcher::MatchDocStringSeparator(Token& token)
    {
        if (activeDocStringSeparator.empty())
        {
            return MatchDocStringSeparator(token, R"(""")", true) || MatchDocStringSeparator(token, "```", true);
        }

        return MatchDocStringSeparator(token, activeDocStringSeparator, false);
    }

    bool TokenMatcher::MatchDocStringSeparator(Token& token, std::string_view separator, bool isOpen)
    {
        if (!token.line.Startswith(separator))
        {
            return false;
        }

        std::string contentType;
        std::string tseparator = std::string(separator);

        if (isOpen)
        {
            contentType = token.line.GetRestTrimmed(separator.size());
            activeDocStringSeparator = tseparator;
            indentToRemove = token.line.Indent();
        }
        else
        {
            activeDocStringSeparator.clear();
            indentToRemove = 0;
        }

        SetTokenMatched(token, RuleType::docStringSeparator, { contentType, tseparator });

        return true;
    }

    void TokenMatcher::SetTokenMatched(Token& token, RuleType matchedType, const TokenInfo& info)
    {
        using namespace std::literals;

        token.matchedType = matchedType;

        if (info.text)
        {
            token.matchedText.assign(Rstrip(*info.text, RePattern::crlf));
        }

        if (info.keyword)
        {
            token.matchedKeyword = *info.keyword;
        }

        token.matchedKeywordType = info.keywordType;

        if (info.indent)
        {
            token.matchedIndent = *info.indent;
        }
        else
        {
            token.matchedIndent = token.line.Indent();
        }

        token.matchedItems = info.items;
        token.location.column = token.matchedIndent + 1;
        token.matchedGherkinDialect = dialectName;
    }

    const StringViews& TokenMatcher::Keywords(std::string_view keyword) const
    {
        return cucumber::gherkin::Keywords(dialectName, keyword);
    }

    messages::StepKeywordType TokenMatcher::KeywordType(std::string_view keyword) const
    {
        auto found = keywordTypes.find(keyword);

        if (found != keywordTypes.end())
        {
            const auto& keywordList = found->second;

            if (keywordList.size() == 1)
            {
                return keywordList[0];
            }
        }

        return messages::StepKeywordType::UNKNOWN;
    }

    void TokenMatcher::ChangeDialect(const std::string& dialectName, const messages::Location& location)
    {
        if (AllKeywords().find(dialectName) == AllKeywords().end())
        {
            throw NoSuchLanguageError(dialectName, location);
        }

        this->dialectName = dialectName;

        auto dialect = GetDialect(dialectName);

        keywordTypes.clear();

        for (const auto& keyword : dialect.givenKeywords)
        {
            keywordTypes[keyword].push_back(messages::StepKeywordType::CONTEXT);
        }

        for (const auto& keyword : dialect.whenKeywords)
        {
            keywordTypes[keyword].push_back(messages::StepKeywordType::ACTION);
        }

        for (const auto& keyword : dialect.thenKeywords)
        {
            keywordTypes[keyword].push_back(messages::StepKeywordType::OUTCOME);
        }

        for (const auto& keyword : dialect.andKeywords)
        {
            keywordTypes[keyword].push_back(messages::StepKeywordType::CONJUNCTION);
        }

        for (const auto& keyword : dialect.butKeywords)
        {
            keywordTypes[keyword].push_back(messages::StepKeywordType::CONJUNCTION);
        }
    }

    std::string TokenMatcher::UnescapeDocstring(const std::string& text) const
    {
        using namespace std::literals;

        std::string unescaped;

        if (activeDocStringSeparator == R"(""")")
        {
            unescaped = Substitute(text, R"(\\"\\"\\")", R"(""")");
        }
        else if (activeDocStringSeparator == "```")
        {
            unescaped = Substitute(text, R"(\\`\\`\\`)", "```");
        }
        else
        {
            unescaped = text;
        }

        return unescaped;
    }

}
