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

    Parser token_parser;

    for (std::size_t i = 1; i < argc; ++i)
    {
        std::string File(argv[i]);

        auto data = cucumber::gherkin::slurp(File);

        auto formatted_tokens = token_parser.parse(File, data);

        std::cout << cucumber::gherkin::join("\n", formatted_tokens);
    }

    std::cout << std::endl;

    return 0;
}
