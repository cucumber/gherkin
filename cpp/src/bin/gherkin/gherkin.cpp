#include <iostream>

#include <cucumber/gherkin/app.hpp>
#include <cucumber/gherkin/file.hpp>

struct options
{
    bool exit = false;
    int exit_code = 0;
    int last_arg = 0;
    bool include_source = true;
    bool include_ast = true;
    bool include_pickles = true;
    bool predicatable_ids = true;
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
        } else if (arg == "--predictable-ids") {
            opts.predicatable_ids = true;
        } else if (arg.find('-') == 0) {
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

template <typename Obj>
void print_json_obj(std::string_view key, const Obj& o)
{
    nlohmann::json j;

    o.to_json(j[key]);

    std::cout << j << std::endl;
}

int main(int ac, char** av)
{
    auto opts = parse_options(ac, av);

    if (opts.exit) {
        return opts.exit_code;
    }

    cucumber::gherkin::app app;
    cucumber::gherkin::app::callbacks cbs{
        .source = [&](const auto& m) { print_json_obj("source", m); },
        .ast = [&](const auto& m) { print_json_obj("gherkinDocument", m); },
        .pickle = [&](const auto& m) { print_json_obj("pickle", m); },
        .error = [&](const auto& m) { std::cout << m.to_json() << std::endl; }
    };

    app.include_source(opts.include_source);
    app.include_ast(opts.include_ast);
    app.include_pickles(opts.include_pickles);

    for ( ; opts.last_arg < ac; ++opts.last_arg) {
        app.parse(cucumber::gherkin::file{ av[opts.last_arg] }, cbs);
    }

    return 0;
}
