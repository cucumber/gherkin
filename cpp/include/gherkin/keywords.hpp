#include <gherkin/dialect.hpp>

namespace gherkin {

const string_views&
keywords(const std::string_view& language, const std::string_view& kw);

string_views
keywords(const std::string_view& language, const string_views& kws);

dialect
get_dialect(const std::string_view& language);

}
