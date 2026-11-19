#ifndef CUCUMBER_GHERKIN_MSG_TYPES_HPP
#define CUCUMBER_GHERKIN_MSG_TYPES_HPP

#include "cucumber/messages/All.hpp"
#include <vector>

namespace cucumber::gherkin
{
    using Pickles = std::vector<messages::Pickle>;
    using PickleSteps = std::vector<messages::PickleStep>;
    using PickleTags = std::vector<messages::PickleTag>;
    using PickleTableCells = std::vector<messages::PickleTableCell>;
    using Steps = std::vector<messages::Step>;
    using Tags = std::vector<messages::Tag>;
    using TableCells = std::vector<messages::TableCell>;
    using Envelopes = std::vector<messages::Envelope>;
}

#endif
