#pragma once

#include <any>
#include <vector>
#include <string>
#include <unordered_map>
#include <optional>
#include <ranges>

#include <gherkin/rule_type.hpp>
#include <gherkin/token.hpp>
#include <gherkin/type_traits.hpp>

namespace gherkin {

class ast_node
{
public:
    ast_node(rule_type rule_type = rule_type::none);
    ast_node(const ast_node& other) = delete;
    ast_node(ast_node&& other);

    virtual ~ast_node();

    ast_node& operator=(const ast_node& other) = delete;
    ast_node& operator=(ast_node&& other);

    bool is(rule_type rule_type) const;

    rule_type type() const;

    template <typename T>
    void add(rule_type rule_type, T&& v)
    {
        using value_type = std::remove_cvref_t<T>;
        using vector_type = std::vector<value_type>;

        auto& a = sub_items_[rule_type];

        if (!a.has_value()) {
            a = vector_type{};
        }

        auto& vs = std::any_cast<vector_type&>(a);
        vs.emplace_back(std::move(v));
    }

    template <typename T>
    auto get_items(rule_type rule_type) const
    {
        using value_type = std::remove_cvref_t<T>;
        using vector_type = std::vector<value_type>;
        using view_type = std::ranges::ref_view<const vector_type>;
        using ret_type = std::optional<view_type>;

        auto it = sub_items_.find(rule_type);

        ret_type r;

        if (it != sub_items_.end()) {
            auto& vs = std::any_cast<const vector_type&>(it->second);

            if (!vs.empty()) {
                r = std::views::all(vs);
            }
        }

        return r;
    }

    template <typename T>
    auto get_single(rule_type rule_type) const
    {
        using value_type = std::remove_cvref_t<T>;
        using ref_type = std::reference_wrapper<const value_type>;
        using ret_type = std::optional<ref_type>;

        auto opt_items = get_items<T>(rule_type);
        ret_type r;

        if (opt_items) {
            auto& items = *opt_items;
            r = std::cref(items[0]);
        }

        return r;
    }

    auto get_tokens(rule_type rule_type) const
    { return *get_items<token>(rule_type); }

    const auto& get_token(rule_type rule_type) const
    { return get_single<token>(rule_type)->get(); }

    template <typename T, typename V = T>
    void set_value(rule_type rule_type, V& v) const
    {
        using type = std::remove_cvref_t<T>;

        if constexpr (is_container_v<std::vector, type>) {
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
            auto item = get_single<type>(rule_type);

            if (item) {
                v = item->get();
            }
        }
    }

    template <typename T>
    void set(rule_type rule_type, T& v) const
    {
        using type = std::remove_cvref_t<T>;

        if constexpr (is_container_v<std::optional, type>) {
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
};

}
