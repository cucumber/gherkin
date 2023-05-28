#pragma once

#include <string>
#include <functional>

#include <gherkin/msg_types.hpp>
#include <gherkin/cb_types.hpp>

namespace gherkin {

struct pickle_compiler_context
{
    std::string next_id();

    void add_pickle(cms::pickle& p);

    pickle_cb sink;
    gherkin::pickles pickles;
    std::size_t id_counter_ = 0;
};

}
