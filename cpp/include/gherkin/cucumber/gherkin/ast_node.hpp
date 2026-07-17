#ifndef CUCUMBER_GHERKIN_AST_NODE_HPP
#define CUCUMBER_GHERKIN_AST_NODE_HPP

#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/type_traits.hpp"
#include <any>
#include <memory>
#include <optional>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace cucumber::gherkin
{
    class AstNode
    {
    public:
        AstNode(RuleType ruleType = RuleType::none);
        AstNode(const AstNode& other);
        AstNode(AstNode&& other) noexcept;

        virtual ~AstNode() = default;

        AstNode& operator=(const AstNode& other);
        AstNode& operator=(AstNode&& other) noexcept;

        bool Is(RuleType ruleType);

        [[nodiscard]] RuleType Type() const;

        template<typename T>
        void Add(RuleType ruleType, const T& value);

        template<typename T>
        [[nodiscard]] const std::vector<T>* GetItems(RuleType ruleType, const std::vector<T>* defaultResult = nullptr) const;

        template<typename T>
        [[nodiscard]] const T* GetSingle(RuleType ruleType, const T* defaultResult = nullptr) const;

        [[nodiscard]] const std::vector<Token>& GetTokens(RuleType ruleType) const;

        [[nodiscard]] const Token& GetToken(RuleType ruleType) const;

        template<typename T, typename V = T>
        void SetValue(RuleType ruleType, V& value) const;

        template<typename T, typename V = T>
        void SetValue(RuleType ruleType, std::shared_ptr<V>& value) const;

        // Overload for optional<shared_ptr<T>>: retrieve T, wrap in shared_ptr
        template<typename T>
        void Set(RuleType ruleType, std::optional<std::shared_ptr<T>>& value) const;

        // Overload for vector<shared_ptr<T>>: retrieve vector<T>, wrap each in shared_ptr
        template<typename T>
        void Set(RuleType ruleType, std::vector<std::shared_ptr<T>>& value) const;

        template<typename T>
        void Set(RuleType ruleType, T& value) const;

    private:
        using SubItems = std::unordered_map<RuleType, std::any>;

        RuleType ruleType;
        SubItems subItems;
        Token nullToken;
        std::vector<Token> emptyTokens;
    };

    template<typename T>
    void AstNode::Add(RuleType ruleType, const T& value)
    {
        auto& entry = subItems[ruleType];

        if (!entry.has_value())
        {
            entry = std::vector<T>{};
        }

        std::any_cast<std::vector<T>&>(entry).push_back(value);
    }

    template<typename T>
    const std::vector<T>* AstNode::GetItems(RuleType ruleType, const std::vector<T>* defaultResult) const
    {
        auto found = subItems.find(ruleType);

        if (found != subItems.end())
        {
            return std::any_cast<std::vector<T>>(&found->second);
        }

        return defaultResult;
    }

    template<typename T>
    const T* AstNode::GetSingle(RuleType ruleType, const T* defaultResult) const
    {
        auto items = GetItems<T>(ruleType);

        if (items && !items->empty())
        {
            return std::addressof(items->at(0));
        }

        return defaultResult;
    }

    template<typename T, typename V>
    void AstNode::SetValue(RuleType ruleType, V& value) const
    {
        using Type = std::decay_t<T>;

        if constexpr (isSpecializationOfV<Type, std::vector>)
        {
            using ValueType = typename Type::ValueType;

            auto optItems = GetItems<ValueType>(ruleType);

            if (optItems)
            {
                auto& items = *optItems;

                for (const auto& element : items)
                {
                    value.emplace_back(element);
                }
            }
        }
        else
        {
            auto pitem = GetSingle<Type>(ruleType);

            if (pitem)
            {
                value = *pitem;
            }
        }
    }

    template<typename T, typename V>
    void AstNode::SetValue(RuleType ruleType, std::shared_ptr<V>& value) const
    {
        SetValue<T>(ruleType, *value);
    }

    // Overload for optional<shared_ptr<T>>: retrieve T, wrap in shared_ptr
    template<typename T>
    void AstNode::Set(RuleType ruleType, std::optional<std::shared_ptr<T>>& value) const
    {
        auto pitem = GetSingle<T>(ruleType);
        if (pitem)
        {
            value = std::make_shared<T>(*pitem);
        }
    }

    // Overload for vector<shared_ptr<T>>: retrieve vector<T>, wrap each in
    // shared_ptr
    template<typename T>
    void AstNode::Set(RuleType ruleType, std::vector<std::shared_ptr<T>>& value) const
    {
        auto optItems = GetItems<T>(ruleType);
        if (optItems)
        {
            for (const auto& item : *optItems)
            {
                value.emplace_back(std::make_shared<T>(item));
            }
        }
    }

    template<typename T>
    void AstNode::Set(RuleType ruleType, T& value) const
    {
        using Type = std::decay_t<T>;

        if constexpr (isSpecializationOfV<Type, std::optional>)
        {
            using ValueType = typename Type::ValueType;

            SetValue<ValueType>(ruleType, value);
        }
        else
        {
            SetValue<Type>(ruleType, value);
        }
    }
}

#endif
