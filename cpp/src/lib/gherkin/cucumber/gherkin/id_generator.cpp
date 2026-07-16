#include "cucumber/gherkin/id_generator.hpp"
#include <string>

namespace cucumber::gherkin
{

    IdGeneratorBase::IdGeneratorBase()
    {}

    IdGeneratorBase::~IdGeneratorBase()
    {}

    IdGenerator::IdGenerator()
    {}

    IdGenerator::~IdGenerator()
    {}

    std::string IdGenerator::next_id()
    {
        return std::to_string(id_counter_++);
    }

}
