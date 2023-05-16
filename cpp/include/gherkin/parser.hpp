#pragma once

#include <gherkin/parser_base.hpp>

namespace gherkin {

class parser : public parser_base
{
public:
    using parser_base::parser_base;
    using parser_base::parse;

    const cms::gherkin_document& parse(const cms::source& source) override;
};

}
