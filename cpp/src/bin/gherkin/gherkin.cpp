#include <iostream>

#include <gherkin/parser.hpp>

struct options
{
    bool print_source_events;
    bool print_ast_events;
    bool print_pickle_events;
};

int main(int ac, char** av)
{
    gherkin::parser p;

    const auto& d = p.parse(gherkin::file{ av[1] });

    std::cout << d.to_json() << std::endl;

    return 0;
}
