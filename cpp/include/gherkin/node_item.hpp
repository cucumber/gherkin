#pragma once

#include <variant>
#include <vector>
#include <unordered_map>
#include <memory>

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

struct null_node_item {};

using node_item = std::variant<
    null_node_item,
    std::unique_ptr<cucumber::messages::background>,
    std::unique_ptr<cucumber::messages::comment>,
    std::unique_ptr<cucumber::messages::data_table>,
    std::unique_ptr<cucumber::messages::doc_string>,
    std::unique_ptr<cucumber::messages::envelope>,
    std::unique_ptr<cucumber::messages::examples>,
    std::unique_ptr<cucumber::messages::feature>,
    std::unique_ptr<cucumber::messages::feature_child>,
    std::unique_ptr<cucumber::messages::gherkin_document>,
    std::unique_ptr<cucumber::messages::location>,
    std::unique_ptr<cucumber::messages::rule>,
    std::unique_ptr<cucumber::messages::rule_child>,
    std::unique_ptr<cucumber::messages::scenario>,
    std::unique_ptr<cucumber::messages::step>,
    std::unique_ptr<cucumber::messages::table_cell>,
    std::unique_ptr<cucumber::messages::table_row>,
    std::unique_ptr<cucumber::messages::tag>,
    std::unique_ptr<token>,
    std::unique_ptr<tokens>
>;

using node_items = std::vector<node_item>;
using node_items_map = std::unordered_map<rule_type, node_items>;

}
