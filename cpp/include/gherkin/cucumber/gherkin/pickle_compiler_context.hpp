#ifndef CUCUMBER_GHERKIN_PICKLE_COMPILER_CONTEXT_HPP
#define CUCUMBER_GHERKIN_PICKLE_COMPILER_CONTEXT_HPP

#include "cucumber/gherkin/cb_types.hpp"
#include "cucumber/gherkin/id_generator.hpp"
#include "cucumber/gherkin/msg_types.hpp"
#include <cstddef>
#include <cucumber/messages/Pickle.hpp>
#include <string>

namespace cucumber::gherkin
{

    struct PickleCompilerContext
    {
        std::string next_id();

        void add_pickle(cms::Pickle& pickle);

        id_generator_ptr idp;
        pickle_cb sink;
        cucumber::gherkin::pickles pickles;
        std::size_t id_counter_ = 0;
    };

}

#endif
