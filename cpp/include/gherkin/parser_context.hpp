#pragma once

#include <gherkin/token.hpp>
#include <gherkin/token_scanner.hpp>
#include <gherkin/token_matcher.hpp>
#include <gherkin/types.hpp>

namespace gherkin {

struct parser_context
{
    gherkin::token_scanner& token_scanner;
    gherkin::token_matcher& token_matcher;
    gherkin::token_queue token_queue;
    gherkin::strings errors;

    bool has_token() const;

    gherkin::token pop_token();
    void push_tokens(const gherkin::token_queue& queue);

    bool has_errors() const;
};

}
