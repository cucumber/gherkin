#include <cucumber/messages/step.hpp>

#include <gherkin/ast_builder.hpp>

namespace gherkin {

ast_builder::ast_builder()
{}

ast_builder::~ast_builder()
{}

void
ast_builder::reset()
{}

void
ast_builder::start_rule(rule_type rule_type)
{ stack_.emplace(rule_type); }

void
ast_builder::end_rule(rule_type rule_type)
{
    auto n = pop_node();
    auto rt = n.type();
    auto p = transform_node(n);

    current_node().add(rt, std::move(p));
}

void
build(token& token)
{}

std::string
ast_builder::next_id()
{ return std::to_string(id_counter_++); }

node_item
ast_builder::transform_node(ast_node& node)
{
    if (node.is(rule_type::step)) {
        const auto& step_line = node.get_token(rule_type::step_line);
        const auto& data_table = node.get_single(rule_type::data_table);
        const auto& doc_string = node.get_single(rule_type::doc_string);

        cucumber::messages::step s{
            .location = get_location(step_line),
            .keyword = step_line.matched_keyword,
            .keyword_type = step_line.matched_keyword_type,
            .text = step_line.matched_text,
            .id = next_id()
        };
    }

    return {};
}

cucumber::messages::location
ast_builder::get_location(
    const token& token,
    std::size_t column
) const
{
    return {};
}

ast_node
ast_builder::pop_node()
{
    ast_node n = std::move(current_node());

    stack_.pop();

    return n;
}

ast_node&
ast_builder::current_node()
{ return stack_.top(); }

const ast_node&
ast_builder::current_node() const
{ return stack_.top(); }

}
