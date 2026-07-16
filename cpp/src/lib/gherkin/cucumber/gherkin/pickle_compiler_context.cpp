#include "cucumber/gherkin/pickle_compiler_context.hpp"
#include "cucumber/messages/Pickle.hpp"
#include <string>
#include <utility>

namespace cucumber::gherkin
{

    std::string pickle_compiler_context::next_id()
    {
        return idp->next_id();
    }

    void pickle_compiler_context::add_pickle(cms::Pickle& pickle)
    {
        if (sink)
        {
            sink(pickle);
        }

        pickles.emplace_back(std::move(pickle));
    }

}
