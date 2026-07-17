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
        std::string NextId();

        void AddPickle(messages::Pickle& pickle);

        IdGeneratorPtr idp;
        PickleCb sink;
        cucumber::gherkin::Pickles pickles;
        std::size_t idCounter = 0;
    };

}

#endif
