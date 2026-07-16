#ifndef CUCUMBER_GHERKIN_APP_HPP
#define CUCUMBER_GHERKIN_APP_HPP

#include "cucumber/gherkin/cb_types.hpp"
#include "cucumber/gherkin/file.hpp"
#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/parser.hpp"
#include "cucumber/messages/Envelope.hpp"

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

        void include_source(bool enabled);
        void include_ast(bool enabled);
        void include_pickles(bool enabled);

        void parse(const File& source_file, const Callbacks& Callbacks = {});
        void parse(const cms::Envelope& envelope, const Callbacks& Callbacks = {});
        void parse(const cms::Source& source, const Callbacks& Callbacks = {});

    private:
        void send_parse_error(const std::string& uri, const ParserError& error, const Callbacks& Callbacks) const;

        id_generator_ptr idp_;
        Parser p_;
        bool include_source_ = true;
        bool include_ast_ = true;
        bool include_pickles_ = true;
    };

}

#endif
