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

    void app::include_source(bool f)
    {
        include_source_ = f;
    }

    void app::include_ast(bool f)
    {
        include_ast_ = f;
    }

    void app::include_pickles(bool f)
    {
        include_pickles_ = f;
    }

    void app::parse(const file& f, const callbacks& cbs)
    {
        cms::Envelope e;

        e.source = std::make_shared<cms::Source>(cms::Source{ f.path, slurp(f.path) });

        parse(e, cbs);
    }

    void app::parse(const cms::Envelope& e, const callbacks& cbs)
    {
        if (include_source_ && cbs.source && e.source)
        {
            cbs.source(**e.source);
        }

        if (e.source)
        {
            parse(*(*e.source), cbs);
        }
    }

    void app::parse(const cms::Source& s, const callbacks& cbs)
    {
        try
        {
            auto ast = p_.parse(s.uri, s.data);

            if (include_ast_ && cbs.ast)
            {
                cbs.ast(ast);
            }

            if (include_pickles_ && cbs.pickle)
            {
                pickle_compiler pc(idp_);

                pc.compile(ast, s.uri, cbs.pickle);
            }
        }
        catch (const composite_parser_error& e)
        {
            for (const auto& ep : e.errors())
            {
                send_parse_error(s.uri, *ep, cbs);
            }
        }
        catch (const parser_error& e)
        {
            send_parse_error(s.uri, e, cbs);
        }
    }

    void app::send_parse_error(const std::string& uri, const parser_error& e, const callbacks& cbs) const
    {
        parse_error pe{ uri, e.location(), e.what() };

        call_cb(cbs.error, pe);
    }

}
