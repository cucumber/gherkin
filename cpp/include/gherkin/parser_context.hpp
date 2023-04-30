#pragma once

#include <gherkin/token_scanner.hpp>
#include <gherkin/token_matcher.hpp>
#include <gherkin/types.hpp>

namespace gherkin {

struct parser_context
{
    token_scanner& token_scanner;
    token_matcher& token_matcher;
    token_queue token_queue;
    strings errors;

    bool has_token() const;
    bool has_errors() const;
};

}
