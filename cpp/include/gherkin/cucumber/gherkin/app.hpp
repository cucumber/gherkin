#pragma once

#include "cucumber/gherkin/cb_types.hpp"
#include "cucumber/gherkin/file.hpp"
#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/parser.hpp"
#include "cucumber/messages/Envelope.hpp"

namespace cucumber::gherkin
{

    class app
    {
    public:
        using parser = cucumber::gherkin::parser<>;
        using parser_result = typename parser::result_type;
        using callbacks = cucumber::gherkin::callbacks<parser_result>;

        app();
        virtual ~app();

        void include_source(bool enabled);
        void include_ast(bool enabled);
        void include_pickles(bool enabled);

        void parse(const file& source_file, const callbacks& callbacks = {});
        void parse(const cms::Envelope& envelope, const callbacks& callbacks = {});
        void parse(const cms::Source& source, const callbacks& callbacks = {});

    private:
        void send_parse_error(const std::string& uri, const parser_error& error, const callbacks& callbacks) const;

        id_generator_ptr idp_;
        parser p_;
        bool include_source_ = true;
        bool include_ast_ = true;
        bool include_pickles_ = true;
    };

}
