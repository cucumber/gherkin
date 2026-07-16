#include "cucumber/gherkin/app.hpp"
#include "cucumber/gherkin/file.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string_view>

struct Options
{
    bool exit = false;
    int exit_code = 0;
    int last_arg = 0;
    bool include_source = true;
    bool include_ast = true;
    bool include_pickles = true;
    bool predicatable_ids = true;
};

Options parse_options(int argc, char** argv)
{
    Options opts;

    for (opts.last_arg = 1; opts.last_arg < argc; ++opts.last_arg)
    {
        std::string_view arg(argv[opts.last_arg]);

        if (arg == "--no-source")
        {
            opts.include_source = false;
        }
        else if (arg == "--no-ast")
        {
            opts.include_ast = false;
        }
        else if (arg == "--no-pickles")
        {
            opts.include_pickles = false;
        }
        else if (arg == "--predictable-ids")
        {
            opts.predicatable_ids = true;
        }
        else if (arg.find('-') == 0)
        {
            if (arg != "-h" && arg != "--help")
            {
                std::cout << "Unknown option: " << arg << std::endl;
                opts.exit_code = 1;
            }

            std::cout << "Usage: gherkin [options] FILE...\n"
                      << "    -h, --help       You're looking at it.\n"
                      << "    --no-ast         Do not emit Ast events.\n"
                      << "    --no-pickles     Do not emit Pickle events.\n"
                      << "    --no-source      Do not emit Source events." << std::endl;

            opts.exit = true;
        }
        else
        {
            break;
        }
    }

    return opts;
}

template<typename ObjectType>
void print_json_obj(std::string_view key, const ObjectType& value)
{
    nlohmann::json json_doc;

    value.to_json(json_doc[key]);

    std::cout << json_doc << std::endl;
}

int main(int argc, char** argv)
{
    auto opts = parse_options(argc, argv);

    if (opts.exit)
    {
        return opts.exit_code;
    }

    cucumber::gherkin::App App;
    cucumber::gherkin::App::Callbacks cbs{ [&](const auto& msg)
        {
            print_json_obj("source", msg);
        },
        [&](const auto& msg)
        {
            print_json_obj("gherkinDocument", msg);
        },
        [&](const auto& msg)
        {
            print_json_obj("pickle", msg);
        },
        [&](const auto& msg)
        {
            std::cout << msg.to_json() << std::endl;
        } };

    App.include_source(opts.include_source);
    App.include_ast(opts.include_ast);
    App.include_pickles(opts.include_pickles);

    for (; opts.last_arg < argc; ++opts.last_arg)
    {
        App.parse(cucumber::gherkin::File{ argv[opts.last_arg] }, cbs);
    }

    return 0;
}
