#pragma once

#include <cucumber/messages/source.hpp>

#include <gherkin/ast_builder.hpp>
#include <gherkin/token_scanner.hpp>
#include <gherkin/token_matcher.hpp>
#include <gherkin/file.hpp>

namespace gherkin {

namespace cms = cucumber::messages;

struct parser_info
{
    std::string language = "en";
};

class parser_base
{
public:
    parser_base(const parser_info& pi = {});
    virtual ~parser_base();

    const cms::gherkin_document& parse(const std::string& data);
    const cms::gherkin_document& parse(const gherkin::file& file);

    // Concrete implementation in derived classes
    virtual const cms::gherkin_document& parse(const cms::source& source) = 0;

    const cms::gherkin_document& get_result() const;

protected:
    void reset(const cms::source& source);

    parser_info pi_;
    ast_builder builder_;
    token_scanner scanner_;
    token_matcher matcher_;
};

}
