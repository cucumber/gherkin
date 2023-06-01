#pragma once

#include <cucumber/messages/envelope.hpp>

#include <gherkin/file.hpp>
#include <gherkin/parser.hpp>
#include <gherkin/cb_types.hpp>
#include <gherkin/id_generator.hpp>

namespace gherkin {

class app
{
public:
    using parser = gherkin::parser<>;
    using parser_result = typename parser::result_type;
    using callbacks = gherkin::callbacks<parser_result>;

    app();
    virtual ~app();

    void include_source(bool f);
    void include_ast(bool f);
    void include_pickles(bool f);

    void parse(const file& f, const callbacks& cbs = {});
    void parse(const cms::envelope& e, const callbacks& cbs = {});
    void parse(const cms::source& s, const callbacks& cbs = {});

private:
    void send_parse_error(
        const std::string& uri,
        const parser_error& e,
        const callbacks& cbs
    ) const;

    id_generator_ptr idp_;
    parser p_;
    bool include_source_ = true;
    bool include_ast_ = true;
    bool include_pickles_ = true;
};

}
