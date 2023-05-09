#pragma once

#include <variant>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <type_traits>

#include <cucumber/messages/background.hpp>
#include <cucumber/messages/comment.hpp>
#include <cucumber/messages/data_table.hpp>
#include <cucumber/messages/doc_string.hpp>
#include <cucumber/messages/envelope.hpp>
#include <cucumber/messages/examples.hpp>
#include <cucumber/messages/feature.hpp>
#include <cucumber/messages/feature_child.hpp>
#include <cucumber/messages/gherkin_document.hpp>
#include <cucumber/messages/location.hpp>
#include <cucumber/messages/rule.hpp>
#include <cucumber/messages/rule_child.hpp>
#include <cucumber/messages/scenario.hpp>
#include <cucumber/messages/step.hpp>
#include <cucumber/messages/table_cell.hpp>
#include <cucumber/messages/table_row.hpp>
#include <cucumber/messages/tag.hpp>

#include <gherkin/rule_type.hpp>
#include <gherkin/token.hpp>

namespace gherkin {

class ast_node;

using ast_nodes = std::vector<ast_node>;

using ast_node_data = std::variant<
    ast_nodes,
    std::vector<cucumber::messages::background>,
    std::vector<cucumber::messages::comment>,
    std::vector<cucumber::messages::data_table>,
    std::vector<cucumber::messages::doc_string>,
    std::vector<cucumber::messages::envelope>,
    std::vector<cucumber::messages::examples>,
    std::vector<cucumber::messages::feature>,
    std::vector<cucumber::messages::feature_child>,
    std::vector<cucumber::messages::gherkin_document>,
    std::vector<cucumber::messages::location>,
    std::vector<cucumber::messages::rule>,
    std::vector<cucumber::messages::rule_child>,
    std::vector<cucumber::messages::scenario>,
    std::vector<cucumber::messages::step>,
    std::vector<cucumber::messages::table_cell>,
    std::vector<cucumber::messages::table_row>,
    std::vector<cucumber::messages::tag>,
    strings,
    tokens
>;

using ast_node_items = std::unordered_map<rule_type, ast_node_data>;

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

    template <typename T>
    void add(rule_type rule_type, T&& v)
    {
    }

    template <typename T>
    auto& get_items(rule_type rule_type)
    {
        using type = std::remove_reference_t<T>;
        using vtype = std::vector<type>;

        return std::get<vtype>(sub_items_[rule_type]);
    }

    template <typename T>
    auto& get_single(rule_type rule_type)
    { return get_items<T>(rule_type).front(); }

    auto& get_tokens(rule_type rule_type)
    { return get_items<token>(rule_type); }

    auto& get_token(rule_type rule_type)
    { return get_single<token>(rule_type); }

    template <typename T, typename Callable>
    void visit_items(rule_type rule_type, Callable cb)
    {
        using type = std::remove_reference_t<T>;
        using vtype = std::vector<type>;

        auto it = sub_items_.find(rule_type);

        if (it == sub_items_.end()) {
            return;
        }

        auto& items = std::get<vtype>(it->second);

        if (!items.empty()) {
            cb(items);
        }
    }

    template <typename T, typename Callable>
    void visit_item(rule_type rule_type, Callable cb)
    {
        visit_items<T>(
            rule_type,
            [&cb](auto& items) {
                if (!items.empty()) {
                    cb(items.front());
                }
            }
        );
    }

    template <typename T>
    void set_from_single(rule_type rule_type, T&& v)
    { visit_item<T>(rule_type, [&](auto& item) { v = item; } ); }

    template <typename T>
    void set_from_items(rule_type rule_type, std::vector<T>& vs)
    {
        visit_items<T>(
            rule_type,
            [&](auto& items) {
                std::copy(
                    items.begin(), items.end(),
                    std::back_inserter(vs)
                );
            }
        );
    }

private:
    rule_type rule_type_;
    ast_node_items sub_items_;
};

}
