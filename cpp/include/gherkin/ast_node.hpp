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

    void add(rule_type rule_type, node_item&& m);

    template <typename T>
    auto get_single(rule_type rule_type)
    {
        using ptr_type = std::unique_ptr<T>;
        using ret_type = std::optional<std::reference_wrapper<T>>;
        ret_type r;

        auto it = sub_items_.find(rule_type);

        if (it != sub_items_.end()) {
            auto& items = it->second;

            if (!items.empty()) {
                auto& p = std::get<ptr_type>(items.front());
                r = std::ref(*p);
            }
        }

        return r;
    }

    auto get_token(rule_type rule_type)
    { return get_single<token>(rule_type); }

private:
    rule_type rule_type_;
    node_items_map sub_items_;
};

}
