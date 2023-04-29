#pragma once

#include <gherkin/ast_builder.hpp>
#include <gherkin/token_scanner.hpp>

namespace gherkin {

struct parser_info
{
    ast_builer& builder;
    std::string language = "en";
};

class parser
{
public:
    parser(const parser_info& pi);
    virtual ~parser();

    v

private:
    parser_info pi_;
    token_scanner ts_;
};

}
