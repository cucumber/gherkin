#include <gherkin/parser_context.hpp>

namespace gherkin {

bool
parser_context::has_token() const
{ return !token_queue.empty(); }

gherkin::token
parser_context::pop_token()
{
    auto t = std::move(token_queue.front());
    token_queue.pop_front();

    return t;
}

void
parser_context::push_tokens(const gherkin::token_queue& queue)
{ token_queue.insert(token_queue.end(), queue.begin(), queue.end()); }

bool
parser_context::has_errors() const
{ return !errors.empty(); }

}
