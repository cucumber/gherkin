#pragma once

#include <cucumber/messages/all.hpp>

#include <gherkin/token.hpp>
#include <gherkin/generated/rule_type.hpp>
#include <gherkin/ast_node.hpp>
#include <gherkin/id_generator.hpp>

namespace gherkin {

namespace cms = cucumber::messages;

using table_rows = std::vector<cms::table_row>;
using table_cells = std::vector<cms::table_cell>;
using tags = std::vector<cms::tag>;
using comments = std::vector<cms::comment>;

class token_formatter_builder
{
public:
    using result_type = strings;

    token_formatter_builder(id_generator_ptr idp = {});
    virtual ~token_formatter_builder();

    void reset(std::string_view uri);

    void start_rule(rule_type rule_type);
    void end_rule(rule_type rule_type);
    void build(const token& token);

    strings get_result() const;

private:
    std::string format_token(const token& token);

    id_generator_ptr idp_;
    strings formatted_tokens_;
};

}
