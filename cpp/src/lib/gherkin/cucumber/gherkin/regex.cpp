#include "cucumber/gherkin/regex.hpp"
#include "cucumber/gherkin/types.hpp"
#include <regex>
#include <string>

namespace cucumber::gherkin
{

    void split(const std::string& pattern, const std::string& expr, strings& list)
    {
        list.clear();

        if (expr.empty())
        {
            return;
        }

        std::regex delimiter(pattern);

        auto current = std::sregex_token_iterator(expr.begin(), expr.end(), delimiter, -1);
        auto end = std::sregex_token_iterator();

        for (; current != end; ++current)
        {
            list.push_back(*current);
        }

        if (list.empty() && expr.size() > 0)
        {
            list.push_back(expr);
        }
    }

    strings split(const std::string& pattern, const std::string& expr)
    {
        strings list;

        split(pattern, expr, list);

        return list;
    }

    std::string subst(const std::string& source, const std::string& pattern, const std::string& what)
    {
        return std::regex_replace(source, std::regex(pattern), what);
    }

    void subst(std::string& source, const std::string& pattern, const std::string& what)
    {
        source = subst(static_cast<const std::string&>(source), pattern, what);
    }

}
