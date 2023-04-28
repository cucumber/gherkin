#pragma once

#include <gherkin/token_scanner.hpp>

namespace gherkin {

class parser
{
public:
    parser();
    virtual ~parser();

private:
    token_scanner s_;
};

}
