#include <cucumber/gherkin/id_generator.hpp>

namespace cucumber::gherkin {

id_generator_base::id_generator_base()
{}

id_generator_base::~id_generator_base()
{}

id_generator::id_generator()
{}

id_generator::~id_generator()
{}

std::string
id_generator::next_id()
{ return std::to_string(id_counter_++); }

}
