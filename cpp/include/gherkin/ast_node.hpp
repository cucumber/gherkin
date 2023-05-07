#pragma once

#include <memory>
#include <optional>
#include <functional>

#include <gherkin/node_item.hpp>

namespace gherkin {

class ast_node
{
public:
    ast_node(rule_type rule_type);
    ast_node(const ast_node& other) = delete;
    ast_node(ast_node&& other);

    virtual ~ast_node();

    ast_node& operator=(const ast_node& other) = delete;
    ast_node& operator=(ast_node&& other);

    bool is(rule_type rule_type) const;

    rule_type type() const;

    void add(rule_type rule_type, node_item&& n);

    template <typename T>
    void add(rule_type rule_type, T&& v)
    {
        auto n = make_node_item(std::move(v));

        add(n);
    }

    template <typename T>
    auto get_single(rule_type rule_type)
    {
        using type = std::remove_reference_t<T>;
        using ptr_type = std::unique_ptr<type>;
        type* ret = nullptr;

        auto it = sub_items_.find(rule_type);

        if (it != sub_items_.end()) {
            auto& items = it->second;

            if (!items.empty()) {
                auto& p = std::get<ptr_type>(items.front());
                ret = p.get();
            }
        }

        return ret;
    }

    token& get_token(rule_type rule_type)
    { return *get_single<token>(rule_type); }

    tokens& get_tokens(rule_type rule_type)
    { return *get_single<tokens>(rule_type); }

    token& get_first_token(rule_type rule_type)
    { return get_tokens(rule_type).front(); }

    template <typename T>
    void set_from_single(rule_type rule_type, T&& v)
    {
        using type = std::remove_reference_t<decltype(v)>;

        auto p = get_single<type>(rule_type);

        if (p) {
            v = *p;
        }
    }

private:
    rule_type rule_type_;
    node_items_map sub_items_;
};

}
