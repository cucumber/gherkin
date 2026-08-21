#ifndef CUCUMBER_GHERKIN_MSG_TYPES_HPP
#define CUCUMBER_GHERKIN_MSG_TYPES_HPP

#include "cucumber/messages/All.hpp"
#include <memory>
#include <vector>

namespace cucumber::gherkin
{
    using Pickles = std::vector<messages::Pickle>;
    using PickleSteps = std::vector<std::shared_ptr<messages::PickleStep>>;
    using PickleTags = std::vector<std::shared_ptr<messages::PickleTag>>;
    using PickleTableCells = std::vector<std::shared_ptr<messages::PickleTableCell>>;
    using Steps = std::vector<std::shared_ptr<messages::Step>>;
    using Tags = std::vector<std::shared_ptr<messages::Tag>>;
    using TableCells = std::vector<std::shared_ptr<messages::TableCell>>;
    using Envelopes = std::vector<messages::Envelope>;
}

#endif
