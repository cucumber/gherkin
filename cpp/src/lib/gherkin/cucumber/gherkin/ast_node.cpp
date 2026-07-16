#include "cucumber/gherkin/ast_node.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include <utility>

namespace cucumber::gherkin
{

    AstNode::AstNode(RuleType RuleType)
        : rule_type_(RuleType)
    {}

    AstNode::AstNode(const AstNode& other)
        : rule_type_(other.rule_type_)
        , sub_items_(other.sub_items_)
    {}

    AstNode::AstNode(AstNode&& other)
        : rule_type_(std::move(other.rule_type_))
        , sub_items_(std::move(other.sub_items_))
    {}

    AstNode::~AstNode()
    {}

    AstNode& AstNode::operator=(const AstNode& other)
    {
        rule_type_ = other.rule_type_;
        sub_items_ = other.sub_items_;

        return *this;
    }

    AstNode& AstNode::operator=(AstNode&& other)
    {
        rule_type_ = std::move(other.rule_type_);
        sub_items_ = std::move(other.sub_items_);

        return *this;
    }

    bool AstNode::is(RuleType RuleType) const
    {
        return rule_type_ == RuleType;
    }

    RuleType AstNode::type() const
    {
        return rule_type_;
    }

}
