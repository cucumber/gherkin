#pragma once

#include "cucumber/messages/All.hpp"
#include <memory>
#include <vector>

namespace cucumber::gherkin
{

    namespace cms = cucumber::messages;

    using pickles = std::vector<cms::Pickle>;
    using pickle_steps = std::vector<std::shared_ptr<cms::PickleStep>>;
    using pickle_tags = std::vector<std::shared_ptr<cms::PickleTag>>;
    using pickle_table_cells = std::vector<std::shared_ptr<cms::PickleTableCell>>;
    using steps = std::vector<std::shared_ptr<cms::Step>>;
    using tags = std::vector<std::shared_ptr<cms::Tag>>;
    using table_cells = std::vector<std::shared_ptr<cms::TableCell>>;
    using envelopes = std::vector<cms::Envelope>;

}
