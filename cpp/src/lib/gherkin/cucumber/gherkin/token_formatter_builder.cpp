#include "cucumber/gherkin/token_formatter_builder.hpp"
#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/join_utils.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/types.hpp"
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

namespace cucumber::gherkin
{

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

    std::string TokenFormatterBuilder::FormatToken(const Token& token)
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
