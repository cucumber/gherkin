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
       keywords(language, "feature"),
       keywords(language, "rule"),
       keywords(language, "scenario"),
       keywords(language, "scenarioOutline"),
       keywords(language, "background"),
       keywords(language, "examples"),
       keywords(language, "given"),
       keywords(language, "when"),
       keywords(language, "then"),
       keywords(language, "and"),
       keywords(language, "but")
    };
}

}
