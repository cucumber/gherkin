#pragma once

#include <variant>
#include <vector>
#include <unordered_map>

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

using node_item = std::variant<
    cucumber::messages::background,
    cucumber::messages::comment,
    cucumber::messages::data_table,
    cucumber::messages::doc_string,
    cucumber::messages::envelope,
    cucumber::messages::examples,
    cucumber::messages::feature,
    cucumber::messages::feature_child,
    cucumber::messages::gherkin_document,
    cucumber::messages::location,
    cucumber::messages::rule,
    cucumber::messages::rule_child,
    cucumber::messages::scenario,
    cucumber::messages::step,
    cucumber::messages::table_cell,
    cucumber::messages::table_row,
    cucumber::messages::tag,
    token,
    tokens
>;

using node_items = std::vector<node_item>;
using node_items_map = std::unordered_map<rule_type, node_items>;

}
