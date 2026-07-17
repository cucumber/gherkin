#include "cucumber/gherkin/dialect.hpp"
#include "cucumber/gherkin/types.hpp"
#include <string_view>

namespace cucumber::gherkin
{

    const string_views& keywords(const std::string_view& language, const std::string_view& keyword);

    string_views keywords(const std::string_view& language, const string_views& keyword_names);

    Dialect get_dialect(const std::string_view& language);

}
