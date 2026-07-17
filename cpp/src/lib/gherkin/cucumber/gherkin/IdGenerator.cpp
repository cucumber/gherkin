#include "cucumber/gherkin/IdGenerator.hpp"
#include <string>

namespace cucumber::gherkin
{

    std::string IdGenerator::NextId()
    {
        return std::to_string(idCounter++);
    }

}
