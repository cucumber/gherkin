#include "cucumber/gherkin/App.hpp"
#include "cucumber/gherkin/CbTypes.hpp"
#include "cucumber/gherkin/Exceptions.hpp"
#include "cucumber/gherkin/File.hpp"
#include "cucumber/gherkin/IdGenerator.hpp"
#include "cucumber/gherkin/ParseError.hpp"
#include "cucumber/gherkin/PickleCompiler.hpp"
#include "cucumber/gherkin/Utils.hpp"
#include "cucumber/messages/Envelope.hpp"
#include "cucumber/messages/Source.hpp"
#include <memory>
#include <string>

namespace cucumber::gherkin
{
    namespace
    {
        void SendParseError(const std::string& uri, const ParserError& error, const App::Callbacks& callbacks)
        {
            ParseError const errorData{ uri, error.Location(), error.what() };

            CallCb(callbacks.error, errorData);
        }
    }

    App::App()
        : idp(NewIdGenerator())
        , p(idp)
    {}

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
        messages::Envelope envelope;

        envelope.source = std::make_shared<messages::Source>(messages::Source{ sourceFile.path, Slurp(sourceFile.path) });

        Parse(envelope, callbacks);
    }

    void App::Parse(const messages::Envelope& envelope, const Callbacks& callbacks)
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

    void App::Parse(const messages::Source& source, const Callbacks& callbacks)
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

}
