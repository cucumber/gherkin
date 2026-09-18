#include "cucumber/gherkin/Regex.hpp"
#include "cucumber/gherkin/Types.hpp"
#include <regex>
#include <string>

namespace cucumber::gherkin
{

    void Split(const std::string& pattern, const std::string& expr, Strings& list) // NOLINT(bugprone-easily-swappable-parameters)
    {
        list.clear();

        if (expr.empty())
        {
            return;
        }

        std::regex const delimiter(pattern);

        auto current = std::sregex_token_iterator(expr.begin(), expr.end(), delimiter, -1);
        auto end = std::sregex_token_iterator();

        for (; current != end; ++current)
        {
            list.push_back(*current);
        }

        if (list.empty() && !expr.empty())
        {
            list.push_back(expr);
        }
    }

    Strings Split(const std::string& pattern, const std::string& expr)
    {
        Strings list;

        Split(pattern, expr, list);

        return list;
    }

    std::string Substitute(const std::string& source, const std::string& pattern, const std::string& what)
    {
        return std::regex_replace(source, std::regex(pattern), what);
    }

    void Substitute(std::string& source, const std::string& pattern, const std::string& what)
    {
        source = Substitute(static_cast<const std::string&>(source), pattern, what);
    }

}
