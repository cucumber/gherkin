#ifndef CUCUMBER_GHERKIN_APP_HPP
#define CUCUMBER_GHERKIN_APP_HPP

#include "cucumber/gherkin/AstBuilder.hpp"
#include "cucumber/gherkin/CbTypes.hpp"
#include "cucumber/gherkin/File.hpp"
#include "cucumber/gherkin/IdGenerator.hpp"
#include "cucumber/gherkin/Parser.hpp"
#include "cucumber/messages/Envelope.hpp"
#include <cucumber/messages/GherkinDocument.hpp>
#include <cucumber/messages/Source.hpp>

namespace cucumber::gherkin
{
    class App
    {
    public:
        using Parser = cucumber::gherkin::Parser<AstBuilder>;
        using Callbacks = cucumber::gherkin::Callbacks<Parser::ResultType>;

        App();
        virtual ~App() = default;
        App(const App&) = delete;
        App& operator=(const App&) = delete;
        App(App&&) = delete;
        App& operator=(App&&) = delete;

        void IncludeSource(bool enabled);
        void IncludeAst(bool enabled);
        void IncludePickles(bool enabled);

        void Parse(const File& sourceFile, const Callbacks& callbacks = {});
        void Parse(const messages::Envelope& envelope, const Callbacks& callbacks = {});
        void Parse(const messages::Source& source, const Callbacks& callbacks = {});

    private:
        IdGeneratorPtr idp;
        Parser p;
        bool includeSource = true;
        bool includeAst = true;
        bool includePickles = true;
    };

}

#endif
