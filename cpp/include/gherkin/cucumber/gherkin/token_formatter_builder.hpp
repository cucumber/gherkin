#ifndef CUCUMBER_GHERKIN_TOKEN_FORMATTER_BUILDER_HPP
#define CUCUMBER_GHERKIN_TOKEN_FORMATTER_BUILDER_HPP

#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/types.hpp"
#include <string>
#include <string_view>

namespace cucumber::gherkin
{
    class TokenFormatterBuilder
    {
    public:
        using ResultType = Strings;

        TokenFormatterBuilder(IdGeneratorPtr idp = {});
        virtual ~TokenFormatterBuilder();
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
        static std::string FormatToken(const Token& token);

        IdGeneratorPtr idp;
        Strings formattedTokens;
    };

}

#endif
