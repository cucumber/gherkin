#include <gherkin/pickle_compiler_context.hpp>

namespace gherkin {

std::string
pickle_compiler_context::next_id()
{ return std::to_string(id_counter_++); }

void
pickle_compiler_context::add_pickle(cms::pickle& p)
{
    if (sink) {
        sink(p);
    }

    pickles.emplace_back(std::move(p));
}

}
