#pragma once

#include <functional>

#include <gherkin/ast_builder.hpp>
#include <gherkin/token_scanner.hpp>
#include <gherkin/token_matcher.hpp>
#include <gherkin/file.hpp>

namespace gherkin {

struct parser_info
{
    std::string language = "en";
};

class parser
{
public:
    parser(const parser_info& pi = {});
    virtual ~parser();

    const cms::gherkin_document& parse(const file& file);

    const cms::gherkin_document& get_result() const;

private:
    parser_info pi_;
    ast_builder builder_;
    token_scanner scanner_;
    token_matcher matcher_;
};

}
