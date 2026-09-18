#include "cucumber/gherkin/PickleCompilerContext.hpp"
#include "cucumber/messages/Pickle.hpp"
#include <string>
#include <utility>

namespace cucumber::gherkin
{
    std::string PickleCompilerContext::NextId()
    {
        return idp->NextId();
    }

    void PickleCompilerContext::AddPickle(messages::Pickle& pickle)
    {
        if (sink)
        {
            sink(pickle);
        }

        pickles.emplace_back(std::move(pickle));
    }
}
