#pragma once

#include <vector>

#include <gherkin/msg_types.hpp>

namespace gherkin {

struct data
{
    cms::gherkin_document document;
    gherkin::pickles pickles;
};

}
