#pragma once

#include <cucumber/messages/source.hpp>

#include <gherkin/ast_builder.hpp>
#include <gherkin/token_scanner.hpp>
#include <gherkin/token_matcher.hpp>
#include <gherkin/file.hpp>
#include <gherkin/parser_info.hpp>

namespace gherkin {

namespace cms = cucumber::messages;

class parser_base
{
public:
    parser_base(const parser_info& pi = {});
    virtual ~parser_base();

    void parse(const std::string& data);
    void parse(const gherkin::file& file);

    const cms::gherkin_document& get_result() const;

protected:
    void reset(const cms::source& source);
    void parse_from_source(const cms::source& source);

    // Concrete implementation in derived classes
    virtual const cms::gherkin_document& parse(const cms::source& source) = 0;

    parser_info pi_;
    ast_builder builder_;
    token_scanner scanner_;
    token_matcher matcher_;
};

}
