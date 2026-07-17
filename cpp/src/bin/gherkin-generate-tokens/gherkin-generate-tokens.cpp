#include "cucumber/gherkin/join_utils.hpp"
#include "cucumber/gherkin/parser.hpp"
#include "cucumber/gherkin/token_formatter_builder.hpp"
#include "cucumber/gherkin/utils.hpp"
#include <cstddef>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    using builder = cucumber::gherkin::TokenFormatterBuilder;
    using Parser = cucumber::gherkin::Parser<builder>;

    Parser tokenParser;

    for (std::size_t i = 1; i < argc; ++i)
    {
        std::string const file(argv[i]); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

        auto data = cucumber::gherkin::Slurp(file);

        auto formattedTokens = tokenParser.Parse(file, data);

        std::cout << cucumber::gherkin::Join("\n", formattedTokens);
    }

    std::cout << '\n';

    return 0;
}
