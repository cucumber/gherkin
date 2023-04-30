#pragma once

#include <gherkin/ast_builder.hpp>
#include <gherkin/token.hpp>
#include <gherkin/token_scanner.hpp>
#include <gherkin/types.hpp>
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

    int parse(const file& file);

private:
    void start_rule(parser_context& ctx, )

    parser_info pi_;
    ast_builder ast_builder_;
    token_scanner token_scanner_;
    token_matcher token_matcher_;
};

}
