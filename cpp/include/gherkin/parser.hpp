#pragma once

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
    parser(const parser_info& pi);
    virtual ~parser();

    std::size_t parse(const file& file);

private:
    parser_info pi_;
    ast_builder builder_;
    token_scanner scanner_;
    token_matcher matcher_;
};

}
