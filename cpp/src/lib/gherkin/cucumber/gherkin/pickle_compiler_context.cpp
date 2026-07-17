#include "cucumber/gherkin/pickle_compiler_context.hpp"
#include "cucumber/messages/Pickle.hpp"
#include <string>
#include <utility>

namespace cucumber::gherkin
{
    std::string PickleCompilerContext::NextId()
    {
        return idp->NextId();
    }

    void PickleCompilerContext::AddPickle(cucumber::messages::Pickle& pickle)
    {
        if (sink)
        {
            sink(pickle);
        }

        pickles.emplace_back(std::move(pickle));
    }
}
