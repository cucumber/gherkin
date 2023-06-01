#include <iostream>
#include <string_view>

#include <gherkin/generated/parser.hpp>
#include <gherkin/token_formatter_builder.hpp>
#include <gherkin/join_utils.hpp>
#include <gherkin/utils.hpp>

int main(int ac, char** av)
{
    using builder = gherkin::token_formatter_builder;
    using parser = gherkin::parser<builder>;

    parser p;

    for (std::size_t i = 1; i < ac; ++i) {
        std::string file(av[i]);

        auto data = gherkin::slurp(file);

        auto ss = p.parse(file, data);

        std::cout << gherkin::join("\n", ss);
    }

    std::cout << std::endl;

    return 0;
}
