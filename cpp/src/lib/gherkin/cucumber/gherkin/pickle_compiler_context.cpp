#include "cucumber/gherkin/pickle_compiler_context.hpp"
#include "cucumber/messages/Pickle.hpp"
#include <string>
#include <utility>

namespace cucumber::gherkin
{

    std::string PickleCompilerContext::next_id()
    {
        return idp->next_id();
    }

    void PickleCompilerContext::add_pickle(cms::Pickle& pickle)
    {
        if (sink)
        {
            sink(pickle);
        }

        pickles.emplace_back(std::move(pickle));
    }

}
