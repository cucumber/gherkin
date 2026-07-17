#include "cucumber/gherkin/dialect.hpp"
#include "cucumber/gherkin/types.hpp"
#include <string_view>

namespace cucumber::gherkin
{

    const string_views& Keywords(const std::string_view& language, const std::string_view& keyword);

    string_views Keywords(const std::string_view& language, const string_views& keywordNames);

    Dialect GetDialect(const std::string_view& language);
}
