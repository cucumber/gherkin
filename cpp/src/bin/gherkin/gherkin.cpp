#include "cucumber/gherkin/app.hpp"
#include "cucumber/gherkin/file.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string_view>

namespace
{
    struct Options
    {
        bool exit = false;
        int exitCode = 0;
        int lastArg = 0;
        bool includeSource = true;
        bool includeAst = true;
        bool includePickles = true;
        bool predicatableIds = true;
    };

    Options ParseOptions(int argc, char** argv)
    {
        Options opts;

        for (opts.lastArg = 1; opts.lastArg < argc; ++opts.lastArg)
        {
            std::string_view const arg(argv[opts.lastArg]); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

            if (arg == "--no-source")
            {
                opts.includeSource = false;
            }
            else if (arg == "--no-ast")
            {
                opts.includeAst = false;
            }
            else if (arg == "--no-pickles")
            {
                opts.includePickles = false;
            }
            else if (arg == "--predictable-ids")
            {
                opts.predicatableIds = true;
            }
            else if (arg.find('-') == 0)
            {
                if (arg != "-h" && arg != "--help")
                {
                    std::cout << "Unknown option: " << arg << '\n';
                    opts.exitCode = 1;
                }

                std::cout << "Usage: gherkin [options] FILE...\n"
                          << "    -h, --help       You're looking at it.\n"
                          << "    --no-ast         Do not emit Ast events.\n"
                          << "    --no-pickles     Do not emit Pickle events.\n"
                          << "    --no-source      Do not emit Source events." << '\n';

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
    void PrintJsonObj(std::string_view key, const ObjectType& value)
    {
        nlohmann::json jsonDoc;

        value.to_json(jsonDoc[key]);

        std::cout << jsonDoc << '\n';
    }
}

int main(int argc, char** argv)
{
    auto opts = ParseOptions(argc, argv);

    if (opts.exit)
    {
        return opts.exitCode;
    }

    cucumber::gherkin::App app;
    cucumber::gherkin::App::Callbacks const cbs{ [&](const auto& msg)
        {
            PrintJsonObj("source", msg);
        },
        [&](const auto& msg)
        {
            PrintJsonObj("gherkinDocument", msg);
        },
        [&](const auto& msg)
        {
            PrintJsonObj("pickle", msg);
        },
        [&](const auto& msg)
        {
            std::cout << msg.to_json() << std::endl;
        } };

    app.IncludeSource(opts.includeSource);
    app.IncludeAst(opts.includeAst);
    app.IncludePickles(opts.includePickles);

    for (; opts.lastArg < argc; ++opts.lastArg)
    {
        app.Parse(cucumber::gherkin::File{ argv[opts.lastArg] }, cbs); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }

    return 0;
}
