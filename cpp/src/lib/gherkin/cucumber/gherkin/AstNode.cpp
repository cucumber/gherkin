#include "cucumber/gherkin/AstNode.hpp"
#include "cucumber/gherkin/RuleType.hpp"
#include "cucumber/gherkin/Token.hpp"
#include <utility>
#include <vector>

namespace cucumber::gherkin
{

    AstNode::AstNode(RuleType ruleType)
        : ruleType(ruleType)
    {}

    AstNode::AstNode(const AstNode& other)
        : ruleType(other.ruleType)
        , subItems(other.subItems)
    {}

    AstNode::AstNode(AstNode&& other) noexcept
        : ruleType(other.ruleType)
        , subItems(std::move(other.subItems))
    {}

    AstNode& AstNode::operator=(const AstNode& other)
    {
        ruleType = other.ruleType;
        subItems = other.subItems;

        return *this;
    }

    AstNode& AstNode::operator=(AstNode&& other) noexcept
    {
        ruleType = other.ruleType;
        subItems = std::move(other.subItems);

        return *this;
    }

    bool AstNode::Is(RuleType ruleType)
    {
        return this->ruleType == ruleType;
    }

    RuleType AstNode::Type() const
    {
        return ruleType;
    }

    const std::vector<Token>& AstNode::GetTokens(RuleType ruleType) const
    {
        return *GetItems<Token>(ruleType, &emptyTokens);
    }

    const Token& AstNode::GetToken(RuleType ruleType) const
    {
        return *GetSingle<Token>(ruleType, &nullToken);
    }

}
