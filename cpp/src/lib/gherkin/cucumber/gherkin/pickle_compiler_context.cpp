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

    void pickle_compiler_context::add_pickle(cms::Pickle& p)
    {
        if (sink)
        {
            sink(p);
        }

        pickles.emplace_back(std::move(p));
    }

}
