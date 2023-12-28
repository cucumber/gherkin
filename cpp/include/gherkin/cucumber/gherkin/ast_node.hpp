#pragma once

#include <iostream>
#include <any>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <optional>

#include <cucumber/gherkin/rule_type.hpp>
#include <cucumber/gherkin/token.hpp>
#include <cucumber/gherkin/type_traits.hpp>

namespace cucumber::gherkin {

template <typename T>
struct sub_node
{
    using type = std::decay_t<T>;
    using vector_type = std::vector<type>;
    using ptr_type = std::shared_ptr<vector_type>;

    sub_node(std::any& sub_item)
    : ref_(sub_item)
    {
        if (!ref_.has_value()) {
            ref_ = make();
        }
    }

    static
    auto make()
    { return std::make_shared<vector_type>(); }

    auto& cast()
    { return std::any_cast<ptr_type&>(ref_); }

    auto get_ptr()
    { return cast().get(); }

    auto& get()
    { return *cast(); }

    void emplace_back(const T& v)
    { get().emplace_back(v); }

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

    template <typename T>
    void add(rule_type rule_type, const T& v)
    {
        sub_node<T> sn(sub_items_[rule_type]);

        sn.emplace_back(v);
    }

    template <typename T>
    auto get_items(
        rule_type rule_type,
        const std::vector<T>* default_result = nullptr
    ) const
    {
        using stype = sub_node<T>;
        using ret_type = const typename stype::vector_type*;

        ret_type ret = default_result;

        auto it = sub_items_.find(rule_type);

        if (it != sub_items_.end()) {
            stype sn(const_cast<std::any&>(it->second));

            ret = sn.get_ptr();
        }

        return ret;
    }

    template <typename T>
    const T* get_single(
        rule_type rule_type,
        const T* default_result = nullptr
    ) const
    {
        auto items = get_items<T>(rule_type);

        if (items && !items->empty()) {
            return std::addressof(items->at(0));
        }

        return default_result;
    }

    const auto& get_tokens(rule_type rule_type) const
    { return *get_items<token>(rule_type, &empty_tokens_); }

    const auto& get_token(rule_type rule_type) const
    { return *get_single<token>(rule_type, &null_token_); }

    template <typename T, typename V = T>
    void set_value(rule_type rule_type, V& v) const
    {
        using type = std::decay_t<T>;

        if constexpr (is_specialization_of_v<type, std::vector>) {
            using value_type = typename type::value_type;
            using vector_type = std::vector<value_type>;

            auto opt_items = get_items<value_type>(rule_type);

            if (opt_items) {
                auto& items = *opt_items;

                for (const auto& i : items) {
                    v.emplace_back(i);
                }
            }
        } else {
            auto pitem = get_single<type>(rule_type);

            if (pitem) {
                v = *pitem;
            }
        }
    }

    template <typename T>
    void set(rule_type rule_type, T& v) const
    {
        using type = std::decay_t<T>;

        if constexpr (is_specialization_of_v<type, std::optional>) {
            using value_type = typename type::value_type;

            set_value<value_type>(rule_type, v);
        } else {
            set_value<type>(rule_type, v);
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
