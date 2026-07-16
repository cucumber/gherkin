#include "cucumber/gherkin/join_utils.hpp"
#include "cucumber/gherkin/parser.hpp"
#include "cucumber/gherkin/token_formatter_builder.hpp"
#include "cucumber/gherkin/utils.hpp"
#include <cstddef>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    using builder = cucumber::gherkin::token_formatter_builder;
    using parser = cucumber::gherkin::parser<builder>;

    parser token_parser;

    for (std::size_t i = 1; i < argc; ++i)
    {
        std::string file(argv[i]);

        auto data = cucumber::gherkin::slurp(file);

        auto formatted_tokens = token_parser.parse(file, data);

        std::cout << cucumber::gherkin::join("\n", formatted_tokens);
    }

    std::cout << std::endl;

    return 0;
}
