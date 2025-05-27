#include <cucumber/gherkin/regex.hpp>

namespace cucumber::gherkin {

void
split(const std::string& re, const std::string& expr, strings& list)
{
    list.clear();

    if (expr.empty()) {
        return;
    }

    std::regex delim(re);

    auto cur = std::sregex_token_iterator(
        expr.begin(), expr.end(),
        delim,
        -1
    );
    auto end = std::sregex_token_iterator();

    for( ; cur != end; ++cur ) {
        list.push_back(*cur);
    }

    if (list.empty() && expr.size() > 0) {
        list.push_back(expr);
    }
}

strings
split(const std::string& re, const std::string& expr)
{
    strings list;

    split(re, expr, list);

    return list;
}

std::string
subst(const std::string& s, const std::string& re, const std::string& what)
{
    return std::regex_replace(
        s,
        std::regex(re),
        what
    );
}

void
subst(std::string& s, const std::string& re, const std::string& what)
{ s = subst(static_cast<const std::string&>(s), re, what); }

}
