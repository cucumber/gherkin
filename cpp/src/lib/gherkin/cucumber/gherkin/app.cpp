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
        : idp_(new_id_generator())
        , p_(idp_)
    {}

    App::~App()
    {}

    void App::include_source(bool enabled)
    {
        include_source_ = enabled;
    }

    void App::include_ast(bool enabled)
    {
        include_ast_ = enabled;
    }

    void App::include_pickles(bool enabled)
    {
        include_pickles_ = enabled;
    }

    void App::parse(const File& source_file, const Callbacks& Callbacks)
    {
        cms::Envelope envelope;

        envelope.source = std::make_shared<cms::Source>(cms::Source{ source_file.path, slurp(source_file.path) });

        parse(envelope, Callbacks);
    }

    void App::parse(const cms::Envelope& envelope, const Callbacks& Callbacks)
    {
        if (include_source_ && Callbacks.source && envelope.source)
        {
            Callbacks.source(**envelope.source);
        }

        if (envelope.source)
        {
            parse(*(*envelope.source), Callbacks);
        }
    }

    void App::parse(const cms::Source& source, const Callbacks& Callbacks)
    {
        try
        {
            auto ast = p_.parse(source.uri, source.data);

            if (include_ast_ && Callbacks.ast)
            {
                Callbacks.ast(ast);
            }

            if (include_pickles_ && Callbacks.pickle)
            {
                PickleCompiler compiler(idp_);

                compiler.compile(ast, source.uri, Callbacks.pickle);
            }
        }
        catch (const CompositeParserError& e)
        {
            for (const auto& error_pointer : e.errors())
            {
                send_parse_error(source.uri, *error_pointer, Callbacks);
            }
        }
        catch (const ParserError& e)
        {
            send_parse_error(source.uri, e, Callbacks);
        }
    }

    void App::send_parse_error(const std::string& uri, const ParserError& error, const Callbacks& Callbacks) const
    {
        ParseError error_data{ uri, error.location(), error.what() };

        call_cb(Callbacks.error, error_data);
    }

}
