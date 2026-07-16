#ifndef CUCUMBER_GHERKIN_AST_NODE_HPP
#define CUCUMBER_GHERKIN_AST_NODE_HPP

#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/type_traits.hpp"
#include <any>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace cucumber::gherkin
{

    template<typename T>
    struct sub_node
    {
        using type = std::decay_t<T>;
        using vector_type = std::vector<type>;
        using ptr_type = std::shared_ptr<vector_type>;

        sub_node(std::any& sub_item)
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

    class ast_node
    {
    public:
        ast_node(rule_type rule_type = rule_type::none);
        ast_node(const ast_node& other);
        ast_node(ast_node&& other);

        virtual ~ast_node();

        ast_node& operator=(const ast_node& other);
        ast_node& operator=(ast_node&& other);

        bool is(rule_type rule_type) const;

        rule_type type() const;

        template<typename T>
        void add(rule_type rule_type, const T& value)
        {
            sub_node<T> sub_node_ref(sub_items_[rule_type]);

            sub_node_ref.emplace_back(value);
        }

        template<typename T>
        auto get_items(rule_type rule_type, const std::vector<T>* default_result = nullptr) const
        {
            using stype = sub_node<T>;
            using ret_type = const typename stype::vector_type*;

            ret_type ret = default_result;

            auto found = sub_items_.find(rule_type);

            if (found != sub_items_.end())
            {
                stype sub_node_ref(const_cast<std::any&>(found->second));

                ret = sub_node_ref.get_ptr();
            }

            return ret;
        }

        template<typename T>
        const T* get_single(rule_type rule_type, const T* default_result = nullptr) const
        {
            auto items = get_items<T>(rule_type);

            if (items && !items->empty())
            {
                return std::addressof(items->at(0));
            }

            return default_result;
        }

        const auto& get_tokens(rule_type rule_type) const
        {
            return *get_items<token>(rule_type, &empty_tokens_);
        }

        const auto& get_token(rule_type rule_type) const
        {
            return *get_single<token>(rule_type, &null_token_);
        }

        template<typename T, typename V = T>
        void set_value(rule_type rule_type, V& value) const
        {
            using type = std::decay_t<T>;

            if constexpr (is_specialization_of_v<type, std::vector>)
            {
                using value_type = typename type::value_type;

                auto opt_items = get_items<value_type>(rule_type);

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
                auto pitem = get_single<type>(rule_type);

                if (pitem)
                {
                    value = *pitem;
                }
            }
        }

        template<typename T, typename V = T>
        void set_value(rule_type rule_type, std::shared_ptr<V>& value) const
        {
            set_value<T>(rule_type, *value);
        }

        // Overload for optional<shared_ptr<T>>: retrieve T, wrap in shared_ptr
        template<typename T>
        void set(rule_type rule_type, std::optional<std::shared_ptr<T>>& value) const
        {
            auto pitem = get_single<T>(rule_type);
            if (pitem)
            {
                value = std::make_shared<T>(*pitem);
            }
        }

        // Overload for vector<shared_ptr<T>>: retrieve vector<T>, wrap each in
        // shared_ptr
        template<typename T>
        void set(rule_type rule_type, std::vector<std::shared_ptr<T>>& value) const
        {
            auto opt_items = get_items<T>(rule_type);
            if (opt_items)
            {
                for (const auto& item : *opt_items)
                {
                    value.emplace_back(std::make_shared<T>(item));
                }
            }
        }

        template<typename T>
        void set(rule_type rule_type, T& value) const
        {
            using type = std::decay_t<T>;

            if constexpr (is_specialization_of_v<type, std::optional>)
            {
                using value_type = typename type::value_type;

                set_value<value_type>(rule_type, value);
            }
            else
            {
                set_value<type>(rule_type, value);
            }
        }

    private:
        using sub_items = std::unordered_map<rule_type, std::any>;

        rule_type rule_type_;
        sub_items sub_items_;
        token null_token_;
        std::vector<token> empty_tokens_;
    };

}

#endif
