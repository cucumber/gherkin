#include "cucumber/gherkin/dialect.hpp"
#include "cucumber/gherkin/types.hpp"
#include <string_view>

namespace cucumber::gherkin
{

    const StringViews& Keywords(const std::string_view& language, const std::string_view& keyword);

    StringViews Keywords(const std::string_view& language, const StringViews& keywordNames);

    Dialect GetDialect(const std::string_view& language);
}
