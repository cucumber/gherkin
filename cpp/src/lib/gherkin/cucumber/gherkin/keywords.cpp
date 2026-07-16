#include "cucumber/gherkin/keywords.hpp"
#include "cucumber/gherkin/dialect.hpp"
#include "cucumber/gherkin/types.hpp"
#include <string_view>

namespace cucumber::gherkin
{

    const string_views& keywords(const std::string_view& language, const std::string_view& keyword)
    {
        return all_keywords().at(language).at(keyword);
    }

    string_views keywords(const std::string_view& language, const string_views& keyword_names)
    {
        string_views views;

        for (const auto& keyword : keyword_names)
        {
            auto keyword_views = keywords(language, keyword);
            views.insert(views.end(), keyword_views.begin(), keyword_views.end());
        }

        return views;
    }

    Dialect get_dialect(const std::string_view& language)
    {
        return { keywords(language, "feature"), keywords(language, "rule"), keywords(language, "scenario"), keywords(language, "scenarioOutline"), keywords(language, "background"),
            keywords(language, "examples"), keywords(language, "given"), keywords(language, "when"), keywords(language, "then"), keywords(language, "and"), keywords(language, "but") };
    }

}
