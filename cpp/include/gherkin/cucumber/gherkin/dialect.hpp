#ifndef CUCUMBER_GHERKIN_DIALECT_HPP
#define CUCUMBER_GHERKIN_DIALECT_HPP

#include "cucumber/gherkin/types.hpp"
#include <string_view>
#include <unordered_map>

namespace cucumber::gherkin
{
    using KeywordsMap = std::unordered_map<std::string_view, StringViews>;
    using KeywordsMaps = std::unordered_map<std::string_view, KeywordsMap>;

    struct Dialect
    {
        ~Dialect() = default;
        Dialect(const Dialect&) = delete;
        Dialect(Dialect&&) = delete;
        Dialect& operator=(const Dialect&) = delete;
        Dialect& operator=(Dialect&&) = delete;

        const StringViews& featureKeywords;
        const StringViews& ruleKeywords;
        const StringViews& scenarioKeywords;
        const StringViews& scenarioOutlineKeywords;
        const StringViews& backgroundKeywords;
        const StringViews& examplesKeywords;
        const StringViews& givenKeywords;
        const StringViews& whenKeywords;
        const StringViews& thenKeywords;
        const StringViews& andKeywords;
        const StringViews& butKeywords;
    };

    const KeywordsMaps& AllKeywords();

    const KeywordsMap& Keywords(const std::string_view& language);
}

#endif
