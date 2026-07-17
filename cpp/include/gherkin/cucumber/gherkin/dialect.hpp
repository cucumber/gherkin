#ifndef CUCUMBER_GHERKIN_DIALECT_HPP
#define CUCUMBER_GHERKIN_DIALECT_HPP

#include "cucumber/gherkin/types.hpp"
#include <string_view>
#include <unordered_map>

namespace cucumber::gherkin
{
    using KeywordsMap = std::unordered_map<std::string_view, string_views>;
    using KeywordsMaps = std::unordered_map<std::string_view, KeywordsMap>;

    struct Dialect
    {
        ~Dialect() = default;
        Dialect(const Dialect&) = delete;
        Dialect(Dialect&&) = delete;
        Dialect& operator=(const Dialect&) = delete;
        Dialect& operator=(Dialect&&) = delete;

        const string_views& featureKeywords;
        const string_views& ruleKeywords;
        const string_views& scenarioKeywords;
        const string_views& scenarioOutlineKeywords;
        const string_views& backgroundKeywords;
        const string_views& examplesKeywords;
        const string_views& givenKeywords;
        const string_views& whenKeywords;
        const string_views& thenKeywords;
        const string_views& andKeywords;
        const string_views& butKeywords;
    };

    const KeywordsMaps& AllKeywords();

    const KeywordsMap& Keywords(const std::string_view& language);
}

#endif
