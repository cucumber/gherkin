#include "cucumber/gherkin/TokenFormatterBuilder.hpp"
#include "cucumber/gherkin/IdGenerator.hpp"
#include "cucumber/gherkin/JoinUtils.hpp"
#include "cucumber/gherkin/RuleType.hpp"
#include "cucumber/gherkin/Token.hpp"
#include "cucumber/gherkin/Types.hpp"
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

namespace cucumber::gherkin
{
    namespace
    {
        std::string FormatToken(const Token& token)
        {
            if (token.IsEof())
            {
                return "EOF";
            }

            std::ostringstream stream;

            stream << "(" << token.location.line << ":" << token.location.column.value_or(0) << ")" << token.matchedType << ":";

            if (token.matchedKeyword)
            {
                stream << "(";

                if (token.matchedKeywordType)
                {
                    stream << *token.matchedKeywordType;
                }

                stream << ")" << token.matchedKeyword.value();
            }

            stream << "/" << token.matchedText << "/";

            if (!token.matchedItems.empty())
            {
                Strings items;

                for (const auto& matchedItem : token.matchedItems)
                {
                    items.emplace_back(std::to_string(matchedItem.column) + ":" + matchedItem.text);
                }

                stream << Join(",", items);
            }

            return stream.str();
        }
    }

    TokenFormatterBuilder::TokenFormatterBuilder(IdGeneratorPtr idp)
        : idp(std::move(std::move(idp)))
    {}

    void TokenFormatterBuilder::Reset([[maybe_unused]] std::string_view uri)
    {
        formattedTokens.clear();
    }

    void TokenFormatterBuilder::StartRule(RuleType ruleType)
    {}

    void TokenFormatterBuilder::EndRule(RuleType ruleType)
    {}

    void TokenFormatterBuilder::Build(const Token& token)
    {
        formattedTokens.emplace_back(FormatToken(token));
    }

    Strings TokenFormatterBuilder::GetResult() const
    {
        return formattedTokens;
    }

}
