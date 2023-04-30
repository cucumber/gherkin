#pragma once

#include <gherkin/parser_context.hpp>

namespace gherkin {

bool
parser_context::has_token() const
{ return !token_queue.empty(); }

token
parser_context::pop_token()
{
    auto t = std::move(token_queue.front());
    token_queue.pop_front();

    return t;
}

bool
parser_context::has_errors() const
{ return !errors.empty(); }

}
