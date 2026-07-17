#include "cucumber/gherkin/app.hpp"
#include "cucumber/gherkin/cb_types.hpp"
#include "cucumber/gherkin/exceptions.hpp"
#include "cucumber/gherkin/file.hpp"
#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/parse_error.hpp"
#include "cucumber/gherkin/pickle_compiler.hpp"
#include "cucumber/gherkin/utils.hpp"
#include "cucumber/messages/Envelope.hpp"
#include "cucumber/messages/Source.hpp"
#include <memory>
#include <string>

namespace cucumber::gherkin
{

    App::App()
        : idp(NewIdGenerator())
        , p(idp)
    {}

    App::~App() = default;

    void App::IncludeSource(bool enabled)
    {
        includeSource = enabled;
    }

    void App::IncludeAst(bool enabled)
    {
        includeAst = enabled;
    }

    void App::IncludePickles(bool enabled)
    {
        includePickles = enabled;
    }

    void App::Parse(const File& sourceFile, const Callbacks& callbacks)
    {
        cucumber::messages::Envelope envelope;

        envelope.source = std::make_shared<cucumber::messages::Source>(cucumber::messages::Source{ sourceFile.path, Slurp(sourceFile.path) });

        Parse(envelope, callbacks);
    }

    void App::Parse(const cucumber::messages::Envelope& envelope, const Callbacks& callbacks)
    {
        if (includeSource && callbacks.source && envelope.source)
        {
            callbacks.source(**envelope.source);
        }

        if (envelope.source)
        {
            Parse(*(*envelope.source), callbacks);
        }
    }

    void App::Parse(const cucumber::messages::Source& source, const Callbacks& callbacks)
    {
        try
        {
            auto ast = p.Parse(source.uri, source.data);

            if (includeAst && callbacks.ast)
            {
                callbacks.ast(ast);
            }

            if (includePickles && callbacks.pickle)
            {
                PickleCompiler compiler(idp);

                compiler.Compile(ast, source.uri, callbacks.pickle);
            }
        }
        catch (const CompositeParserError& e)
        {
            for (const auto& errorPointer : e.Errors())
            {
                SendParseError(source.uri, *errorPointer, callbacks);
            }
        }
        catch (const ParserError& e)
        {
            SendParseError(source.uri, e, callbacks);
        }
    }

    void App::SendParseError(const std::string& uri, const ParserError& error, const Callbacks& callbacks)
    {
        ParseError const errorData{ uri, error.Location(), error.what() };

        CallCb(callbacks.error, errorData);
    }

}
