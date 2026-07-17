#ifndef CUCUMBER_GHERKIN_APP_HPP
#define CUCUMBER_GHERKIN_APP_HPP

#include "cucumber/gherkin/cb_types.hpp"
#include "cucumber/gherkin/exceptions.hpp"
#include "cucumber/gherkin/file.hpp"
#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/parser.hpp"
#include "cucumber/messages/Envelope.hpp"
#include <cucumber/messages/Source.hpp>
#include <string>

namespace cucumber::gherkin
{

    class App
    {
    public:
        using Parser = cucumber::gherkin::Parser<>;
        using parser_result = typename Parser::result_type;
        using Callbacks = cucumber::gherkin::Callbacks<parser_result>;

        App();
        virtual ~App();
        App(const App&) = delete;
        App& operator=(const App&) = delete;
        App(App&&) = delete;
        App& operator=(App&&) = delete;

        void IncludeSource(bool enabled);
        void IncludeAst(bool enabled);
        void IncludePickles(bool enabled);

        void Parse(const File& sourceFile, const Callbacks& callbacks = {});
        void Parse(const cms::Envelope& envelope, const Callbacks& callbacks = {});
        void Parse(const cms::Source& source, const Callbacks& callbacks = {});

    private:
        static void SendParseError(const std::string& uri, const ParserError& error, const Callbacks& callbacks);

        id_generator_ptr idp;
        Parser p;
        bool includeSource = true;
        bool includeAst = true;
        bool includePickles = true;
    };

}

#endif
