#include <iostream>
#include <string_view>

#include <cucumber/gherkin/parser.hpp>
#include <cucumber/gherkin/token_formatter_builder.hpp>
#include <cucumber/gherkin/join_utils.hpp>
#include <cucumber/gherkin/utils.hpp>

int main(int ac, char** av)
{
    using builder = cucumber::gherkin::token_formatter_builder;
    using parser = cucumber::gherkin::parser<builder>;

    parser p;

    for (std::size_t i = 1; i < ac; ++i) {
        std::string file(av[i]);

        auto data = cucumber::gherkin::slurp(file);

        auto ss = p.parse(file, data);

        std::cout << cucumber::gherkin::join("\n", ss);
    }

    std::cout << std::endl;

    return 0;
}
