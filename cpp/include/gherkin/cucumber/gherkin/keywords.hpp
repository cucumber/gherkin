#include "cucumber/gherkin/dialect.hpp"

namespace cucumber::gherkin
{

    const string_views& keywords(const std::string_view& language, const std::string_view& keyword);

    string_views keywords(const std::string_view& language, const string_views& keyword_names);

    Dialect get_dialect(const std::string_view& language);

}
