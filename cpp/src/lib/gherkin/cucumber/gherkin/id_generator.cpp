#include "cucumber/gherkin/id_generator.hpp"
#include <string>

namespace cucumber::gherkin
{

    IdGeneratorBase::IdGeneratorBase() = default;

    IdGeneratorBase::~IdGeneratorBase() = default;

    IdGenerator::IdGenerator() = default;

    IdGenerator::~IdGenerator() = default;

    std::string IdGenerator::NextId()
    {
        return std::to_string(idCounter++);
    }

}
