#ifndef CUCUMBER_GHERKIN_MSG_TYPES_HPP
#define CUCUMBER_GHERKIN_MSG_TYPES_HPP

#include "cucumber/messages/All.hpp"
#include <memory>
#include <vector>

namespace cucumber::gherkin
{
    using pickles = std::vector<messages::Pickle>;
    using pickle_steps = std::vector<std::shared_ptr<messages::PickleStep>>;
    using pickle_tags = std::vector<std::shared_ptr<messages::PickleTag>>;
    using pickle_table_cells = std::vector<std::shared_ptr<messages::PickleTableCell>>;
    using steps = std::vector<std::shared_ptr<messages::Step>>;
    using tags = std::vector<std::shared_ptr<messages::Tag>>;
    using table_cells = std::vector<std::shared_ptr<messages::TableCell>>;
    using envelopes = std::vector<messages::Envelope>;

}

#endif
