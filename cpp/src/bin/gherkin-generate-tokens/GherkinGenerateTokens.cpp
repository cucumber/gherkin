#include "cucumber/gherkin/JoinUtils.hpp"
#include "cucumber/gherkin/Parser.hpp"
#include "cucumber/gherkin/TokenFormatterBuilder.hpp"
#include "cucumber/gherkin/Utils.hpp"
#include <cstddef>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    using Builder = cucumber::gherkin::TokenFormatterBuilder;
    using Parser = cucumber::gherkin::Parser<Builder>;

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
