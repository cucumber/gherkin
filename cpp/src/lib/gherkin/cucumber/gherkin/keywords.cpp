#include <cucumber/gherkin/keywords.hpp>
#include <cucumber/gherkin/exceptions.hpp>

namespace cucumber::gherkin {

const string_views&
keywords(const std::string_view& language, const std::string_view& kw)
{ return keywords(language).at(kw); }

string_views
keywords(const std::string_view& language, const string_views& kws)
{
    string_views svs;

    for (const auto& kw : kws) {
        auto ksvs = keywords(language, kw);
        svs.insert(svs.end(), ksvs.begin(), ksvs.end());
    }

    return svs;
}

dialect
get_dialect(const std::string_view& language)
{
    return {
        .feature_keywords = keywords(language, "feature"),
        .rule_keywords = keywords(language, "rule"),
        .scenario_keywords = keywords(language, "scenario"),
        .scenario_outline_keywords = keywords(language, "scenarioOutline"),
        .background_keywords = keywords(language, "background"),
        .examples_keywords = keywords(language, "examples"),
        .given_keywords = keywords(language, "given"),
        .when_keywords = keywords(language, "when"),
        .then_keywords = keywords(language, "then"),
        .and_keywords = keywords(language, "and"),
        .but_keywords = keywords(language, "but")
    };
}

}
