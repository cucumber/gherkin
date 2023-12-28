 #pragma once

#include <cucumber/gherkin/types.hpp>

namespace cucumber::gherkin {

using keywords_map = std::unordered_map<std::string_view, string_views>;
using keywords_maps = std::unordered_map<std::string_view, keywords_map>;

struct dialect
{
    const string_views& feature_keywords;
    const string_views& rule_keywords;
    const string_views& scenario_keywords;
    const string_views& scenario_outline_keywords;
    const string_views& background_keywords;
    const string_views& examples_keywords;
    const string_views& given_keywords;
    const string_views& when_keywords;
    const string_views& then_keywords;
    const string_views& and_keywords;
    const string_views& but_keywords;
};

const keywords_maps&
all_keywords();

const keywords_map&
keywords(const std::string_view& language);

}
