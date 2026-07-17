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

    template<typename T>
    struct SubNode
    {
        using type = std::decay_t<T>;
        using vector_type = std::vector<type>;
        using ptr_type = std::shared_ptr<vector_type>;

        SubNode(std::any& subItem)
            : ref(subItem)
        {
            if (!ref.has_value())
            {
                ref = Make();
            }
        }

        static auto Make()
        {
            return std::make_shared<vector_type>();
        }

        auto& Cast()
        {
            return std::any_cast<ptr_type&>(ref);
        }

        auto GetPtr()
        {
            return Cast().get();
        }

        auto& Get()
        {
            return *Cast();
        }

        void EmplaceBack(const T& value)
        {
            Get().emplace_back(value);
        }

        std::any& ref; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
    };

    class AstNode
    {
    public:
        AstNode(RuleType ruleType = RuleType::none);
        AstNode(const AstNode& other);
        AstNode(AstNode&& other) noexcept;

        virtual ~AstNode();

        AstNode& operator=(const AstNode& other);
        AstNode& operator=(AstNode&& other) noexcept;

        bool Is(RuleType ruleType);

        RuleType Type() const;

        template<typename T>
        void Add(RuleType ruleType, const T& value)
        {
            SubNode<T> subNodeRef(subItems[ruleType]);

            subNodeRef.EmplaceBack(value);
        }

        template<typename T>
        auto GetItems(RuleType ruleType, const std::vector<T>* defaultResult = nullptr) const
        {
            using stype = SubNode<T>;
            using ret_type = const typename stype::vector_type*;

            ret_type ret = defaultResult;

            auto found = subItems.find(ruleType);

            if (found != subItems.end())
            {
                stype subNodeRef(const_cast<std::any&>(found->second)); // NOLINT(cppcoreguidelines-pro-type-const-cast)

                ret = subNodeRef.GetPtr();
            }

            return ret;
        }

        template<typename T>
        const T* GetSingle(RuleType ruleType, const T* defaultResult = nullptr) const
        {
            auto items = GetItems<T>(ruleType);

            if (items && !items->empty())
            {
                return std::addressof(items->at(0));
            }

            return defaultResult;
        }

        const auto& GetTokens(RuleType ruleType) const
        {
            return *GetItems<Token>(ruleType, &emptyTokens);
        }

        const auto& GetToken(RuleType ruleType) const
        {
            return *GetSingle<Token>(ruleType, &nullToken);
        }

        template<typename T, typename V = T>
        void SetValue(RuleType ruleType, V& value) const
        {
            using type = std::decay_t<T>;

            if constexpr (isSpecializationOfV<type, std::vector>)
            {
                using value_type = typename type::value_type;

                auto optItems = GetItems<value_type>(ruleType);

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
                auto pitem = GetSingle<type>(ruleType);

                if (pitem)
                {
                    value = *pitem;
                }
            }
        }

        template<typename T, typename V = T>
        void SetValue(RuleType ruleType, std::shared_ptr<V>& value) const
        {
            SetValue<T>(ruleType, *value);
        }

        // Overload for optional<shared_ptr<T>>: retrieve T, wrap in shared_ptr
        template<typename T>
        void Set(RuleType ruleType, std::optional<std::shared_ptr<T>>& value) const
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
        void Set(RuleType ruleType, std::vector<std::shared_ptr<T>>& value) const
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
        void Set(RuleType ruleType, T& value) const
        {
            using type = std::decay_t<T>;

            if constexpr (isSpecializationOfV<type, std::optional>)
            {
                using value_type = typename type::value_type;

                SetValue<value_type>(ruleType, value);
            }
            else
            {
                SetValue<type>(ruleType, value);
            }
        }

    private:
        using sub_items = std::unordered_map<RuleType, std::any>;

        RuleType ruleType;
        sub_items subItems;
        Token nullToken;
        std::vector<Token> emptyTokens;
    };

}

#endif
