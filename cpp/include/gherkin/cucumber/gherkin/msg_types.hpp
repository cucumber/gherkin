#pragma once

#include <vector>

#include <cucumber/messages/all.hpp>

namespace cucumber::gherkin {

namespace cms = cucumber::messages;

using pickles = std::vector<cms::pickle>;
using pickle_steps = std::vector<cms::pickle_step>;
using pickle_tags = std::vector<cms::pickle_tag>;
using pickle_table_cells = std::vector<cms::pickle_table_cell>;
using steps = std::vector<cms::step>;
using tags = std::vector<cms::tag>;
using table_cells = std::vector<cms::table_cell>;
using envelopes = std::vector<cms::envelope>;

}
