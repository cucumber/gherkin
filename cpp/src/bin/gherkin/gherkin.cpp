#include <iostream>

#include <gherkin/app.hpp>
#include <gherkin/file.hpp>

struct options
{
    bool exit = false;
    int exit_code = 0;
    int last_arg = 0;
    bool include_source = true;
    bool include_ast = true;
    bool include_pickles = true;
};

options
parse_options(int ac, char** av)
{
    options opts;

    for (opts.last_arg = 1; opts.last_arg < ac; ++opts.last_arg) {
        std::string_view arg(av[opts.last_arg]);

        if (arg == "--no-source") {
            opts.include_source = false;
        } else if (arg == "--no-ast") {
            opts.include_ast = false;
        } else if (arg == "--no-pickles") {
            opts.include_pickles = false;
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

    gherkin::app app;
    gherkin::app::callbacks cbs{
        .source = [&](const auto& s) {
            std::cout << s.to_json() << std::endl;
        },
        .ast = [&](const auto& a) {
            nlohmann::json j;

            a.to_json(j["gherkinDocument"]);

            std::cout << j << std::endl;
        },
        .pickle = [&](const auto& p) {
            nlohmann::json j;

            p.to_json(j["pickle"]);

            std::cout << j << std::endl;
        }
    };

    app.include_source(opts.include_source);
    app.include_ast(opts.include_ast);
    app.include_pickles(opts.include_pickles);

    for ( ; opts.last_arg < ac; ++opts.last_arg) {
        app.parse(gherkin::file{ av[opts.last_arg] }, cbs);
    }

    return 0;
}
