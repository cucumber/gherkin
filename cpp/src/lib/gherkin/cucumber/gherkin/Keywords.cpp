#include "cucumber/gherkin/Keywords.hpp"
#include "cucumber/gherkin/Dialect.hpp"
#include "cucumber/gherkin/Types.hpp"
#include <string_view>

namespace cucumber::gherkin
{

    const StringViews& Keywords(const std::string_view& language, const std::string_view& keyword)
    {
        return AllKeywords().at(language).at(keyword);
    }

    StringViews Keywords(const std::string_view& language, const StringViews& keywordNames)
    {
        StringViews views;

        for (const auto& keyword : keywordNames)
        {
            auto keywordViews = Keywords(language, keyword);
            views.insert(views.end(), keywordViews.begin(), keywordViews.end());
        }

        return views;
    }

    Dialect GetDialect(const std::string_view& language)
    {
        return { Keywords(language, "feature"), Keywords(language, "rule"), Keywords(language, "scenario"), Keywords(language, "scenarioOutline"), Keywords(language, "background"),
            Keywords(language, "examples"), Keywords(language, "given"), Keywords(language, "when"), Keywords(language, "then"), Keywords(language, "and"), Keywords(language, "but") };
    }

}
