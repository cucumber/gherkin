#include "cucumber/gherkin/Dialect.hpp"
#include "cucumber/gherkin/Types.hpp"
#include <string_view>

namespace cucumber::gherkin
{
    [[nodiscard]] const StringViews& Keywords(const std::string_view& language, const std::string_view& keyword);

    [[nodiscard]] StringViews Keywords(const std::string_view& language, const StringViews& keywordNames);

    [[nodiscard]] Dialect GetDialect(const std::string_view& language);
}
