#include <iostream>
#include <string_view>

#include <gherkin/parser.hpp>
#include <gherkin/parser_info.hpp>
#include <gherkin/file.hpp>

struct options
{
    bool exit = false;
    int exit_code = 0;
    int last_arg = 0;
    gherkin::parser_info pi;
};

options
parse_options(int ac, char** av)
{
    options opts;

    for (opts.last_arg = 1; opts.last_arg < ac; ++opts.last_arg) {
        std::string_view arg(av[opts.last_arg]);

        if (arg == "--no-source") {
            opts.pi.include_source = false;
        } else if (arg == "--no-ast") {
            opts.pi.include_ast = false;
        } else if (arg == "--no-pickles") {
            opts.pi.include_pickles = false;
        } else if (arg.starts_with('-')) {
            if (arg != "-h" && arg != "--help") {
                std::cout << "Unknown option: " << arg << std::endl;
                opts.exit_code = 1;
            }

            std::cout
                << "Usage: gherkin [options] FILE...\n"
                << "    -h, --help       You're looking at it.\n"
                << "    --no-ast         Do not emit Ast events.\n"
                << "    --no-pickles     Do not emit Pickle events.\n"
                << "    --no-source      Do not emit Source events."
                << std::endl
                ;

            opts.exit = true;
        } else {
            break;
        }
    }

    return opts;
}

int main(int ac, char** av)
{
    auto opts = parse_options(ac, av);

    if (opts.exit) {
        return opts.exit_code;
    }

    gherkin::parser p{opts.pi};

    for ( ; opts.last_arg < ac; ++opts.last_arg) {
        p.parse(gherkin::file{ av[opts.last_arg] });
    }

    return 0;
}
