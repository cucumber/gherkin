#include <iostream>
#include <string_view>

#include <gherkin/parser.hpp>
#include <gherkin/token_formatter_builder.hpp>
#include <gherkin/file.hpp>
#include <gherkin/join_utils.hpp>

int main(int ac, char** av)
{
    using builder = gherkin::token_formatter_builder;
    using parser = gherkin::parser<builder>;

    parser p;

    for (std::size_t i = 1; i < ac; ++i) {
        auto ss = p.parse(gherkin::file{ av[i] });

        std::cout << gherkin::join("\n", ss);
    }

    std::cout << std::endl;

    return 0;
}
