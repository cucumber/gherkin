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

        SubNode(std::any& sub_item)
            : ref_(sub_item)
        {
            if (!ref_.has_value())
            {
                ref_ = make();
            }
        }

        static auto make()
        {
            return std::make_shared<vector_type>();
        }

        auto& cast()
        {
            return std::any_cast<ptr_type&>(ref_);
        }

        auto get_ptr()
        {
            return cast().get();
        }

        auto& get()
        {
            return *cast();
        }

        void emplace_back(const T& value)
        {
            get().emplace_back(value);
        }

        std::any& ref_;
    };

    class AstNode
    {
    public:
        AstNode(RuleType RuleType = RuleType::none);
        AstNode(const AstNode& other);
        AstNode(AstNode&& other);

        virtual ~AstNode();

        AstNode& operator=(const AstNode& other);
        AstNode& operator=(AstNode&& other);

        bool is(RuleType RuleType) const;

        RuleType type() const;

        template<typename T>
        void add(RuleType RuleType, const T& value)
        {
            SubNode<T> sub_node_ref(sub_items_[RuleType]);

            sub_node_ref.emplace_back(value);
        }

        template<typename T>
        auto get_items(RuleType RuleType, const std::vector<T>* default_result = nullptr) const
        {
            using stype = SubNode<T>;
            using ret_type = const typename stype::vector_type*;

            ret_type ret = default_result;

            auto found = sub_items_.find(RuleType);

            if (found != sub_items_.end())
            {
                stype sub_node_ref(const_cast<std::any&>(found->second));

                ret = sub_node_ref.get_ptr();
            }

            return ret;
        }

        template<typename T>
        const T* get_single(RuleType RuleType, const T* default_result = nullptr) const
        {
            auto items = get_items<T>(RuleType);

            if (items && !items->empty())
            {
                return std::addressof(items->at(0));
            }

            return default_result;
        }

        const auto& get_tokens(RuleType RuleType) const
        {
            return *get_items<Token>(RuleType, &empty_tokens_);
        }

        const auto& get_token(RuleType RuleType) const
        {
            return *get_single<Token>(RuleType, &null_token_);
        }

        template<typename T, typename V = T>
        void set_value(RuleType RuleType, V& value) const
        {
            using type = std::decay_t<T>;

            if constexpr (is_specialization_of_v<type, std::vector>)
            {
                using value_type = typename type::value_type;

                auto opt_items = get_items<value_type>(RuleType);

                if (opt_items)
                {
                    auto& items = *opt_items;

                    for (const auto& element : items)
                    {
                        value.emplace_back(element);
                    }
                }
            }
            else
            {
                auto pitem = get_single<type>(RuleType);

                if (pitem)
                {
                    value = *pitem;
                }
            }
        }

        template<typename T, typename V = T>
        void set_value(RuleType RuleType, std::shared_ptr<V>& value) const
        {
            set_value<T>(RuleType, *value);
        }

        // Overload for optional<shared_ptr<T>>: retrieve T, wrap in shared_ptr
        template<typename T>
        void set(RuleType RuleType, std::optional<std::shared_ptr<T>>& value) const
        {
            auto pitem = get_single<T>(RuleType);
            if (pitem)
            {
                value = std::make_shared<T>(*pitem);
            }
        }

        // Overload for vector<shared_ptr<T>>: retrieve vector<T>, wrap each in
        // shared_ptr
        template<typename T>
        void set(RuleType RuleType, std::vector<std::shared_ptr<T>>& value) const
        {
            auto opt_items = get_items<T>(RuleType);
            if (opt_items)
            {
                for (const auto& Item : *opt_items)
                {
                    value.emplace_back(std::make_shared<T>(Item));
                }
            }
        }

        template<typename T>
        void set(RuleType RuleType, T& value) const
        {
            using type = std::decay_t<T>;

            if constexpr (is_specialization_of_v<type, std::optional>)
            {
                using value_type = typename type::value_type;

                set_value<value_type>(RuleType, value);
            }
            else
            {
                set_value<type>(RuleType, value);
            }
        }

    private:
        using sub_items = std::unordered_map<RuleType, std::any>;

        RuleType rule_type_;
        sub_items sub_items_;
        Token null_token_;
        std::vector<Token> empty_tokens_;
    };

}

#endif
