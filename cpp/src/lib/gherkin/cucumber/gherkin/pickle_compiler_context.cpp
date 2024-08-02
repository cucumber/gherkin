#include <cucumber/gherkin/pickle_compiler_context.hpp>

namespace cucumber::gherkin {

std::string
pickle_compiler_context::next_id()
{ return idp->next_id(); }

void
pickle_compiler_context::add_pickle(cms::pickle& p)
{
    if (sink) {
        sink(p);
    }

    pickles.emplace_back(std::move(p));
}

}
