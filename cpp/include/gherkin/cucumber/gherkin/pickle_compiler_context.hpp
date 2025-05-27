#pragma once

#include <string>
#include <functional>

#include <cucumber/gherkin/msg_types.hpp>
#include <cucumber/gherkin/cb_types.hpp>
#include <cucumber/gherkin/id_generator.hpp>

namespace cucumber::gherkin {

struct pickle_compiler_context
{
    std::string next_id();

    void add_pickle(cms::pickle& p);

    id_generator_ptr idp;
    pickle_cb sink;
    cucumber::gherkin::pickles pickles;
    std::size_t id_counter_ = 0;
};

}
