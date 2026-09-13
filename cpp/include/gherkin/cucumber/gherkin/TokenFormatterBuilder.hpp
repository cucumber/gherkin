#ifndef CUCUMBER_GHERKIN_TOKEN_FORMATTER_BUILDER_HPP
#define CUCUMBER_GHERKIN_TOKEN_FORMATTER_BUILDER_HPP

#include "cucumber/gherkin/IdGenerator.hpp"
#include "cucumber/gherkin/RuleType.hpp"
#include "cucumber/gherkin/Token.hpp"
#include "cucumber/gherkin/Types.hpp"
#include <string_view>

namespace cucumber::gherkin
{
    class TokenFormatterBuilder
    {
    public:
        using ResultType = Strings;

        TokenFormatterBuilder(IdGeneratorPtr idp = {});
        virtual ~TokenFormatterBuilder() = default;
        TokenFormatterBuilder(const TokenFormatterBuilder&) = delete;
        TokenFormatterBuilder& operator=(const TokenFormatterBuilder&) = delete;
        TokenFormatterBuilder(TokenFormatterBuilder&&) = delete;
        TokenFormatterBuilder& operator=(TokenFormatterBuilder&&) = delete;

        void Reset(std::string_view uri);

        void StartRule(RuleType ruleType);
        void EndRule(RuleType ruleType);
        void Build(const Token& token);

        [[nodiscard]] Strings GetResult() const;

    private:
        IdGeneratorPtr idp;
        Strings formattedTokens;
    };

}

#endif
