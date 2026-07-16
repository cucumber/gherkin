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

    app::app()
        : idp_(new_id_generator())
        , p_(idp_)
    {}

    app::~app()
    {}

    void app::include_source(bool enabled)
    {
        include_source_ = enabled;
    }

    void app::include_ast(bool enabled)
    {
        include_ast_ = enabled;
    }

    void app::include_pickles(bool enabled)
    {
        include_pickles_ = enabled;
    }

    void app::parse(const file& source_file, const callbacks& callbacks)
    {
        cms::Envelope envelope;

        envelope.source = std::make_shared<cms::Source>(cms::Source{ source_file.path, slurp(source_file.path) });

        parse(envelope, callbacks);
    }

    void app::parse(const cms::Envelope& envelope, const callbacks& callbacks)
    {
        if (include_source_ && callbacks.source && envelope.source)
        {
            callbacks.source(**envelope.source);
        }

        if (envelope.source)
        {
            parse(*(*envelope.source), callbacks);
        }
    }

    void app::parse(const cms::Source& source, const callbacks& callbacks)
    {
        try
        {
            auto ast = p_.parse(source.uri, source.data);

            if (include_ast_ && callbacks.ast)
            {
                callbacks.ast(ast);
            }

            if (include_pickles_ && callbacks.pickle)
            {
                pickle_compiler compiler(idp_);

                compiler.compile(ast, source.uri, callbacks.pickle);
            }
        }
        catch (const composite_parser_error& e)
        {
            for (const auto& error_pointer : e.errors())
            {
                send_parse_error(source.uri, *error_pointer, callbacks);
            }
        }
        catch (const parser_error& e)
        {
            send_parse_error(source.uri, e, callbacks);
        }
    }

    void app::send_parse_error(const std::string& uri, const parser_error& error, const callbacks& callbacks) const
    {
        parse_error error_data{ uri, error.location(), error.what() };

        call_cb(callbacks.error, error_data);
    }

}
