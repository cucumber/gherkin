#pragma once

#include <functional>

#include <gherkin/ast_builder.hpp>
#include <gherkin/parser_context.hpp>
#include <gherkin/rule_type.hpp>
#include <gherkin/types.hpp>
#include <gherkin/file.hpp>

namespace gherkin {

using match_function = std::function<std::size_t(parser_context&, token&)>;
using match_functions = std::unordered_map<std::size_t, match_function>;

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
    void start_rule(parser_context& ctx, rule_type r);
    void end_rule(parser_context& ctx, rule_type r);

    std::size_t get_result() const;

    std::size_t match_token(
        std::size_t state,
        token& token,
        parser_context& context
    );

    token read_token(parser_context& context);

    parser_info pi_;
    ast_builder ast_builder_;
    token_scanner token_scanner_;
    token_matcher token_matcher_;
};

}
