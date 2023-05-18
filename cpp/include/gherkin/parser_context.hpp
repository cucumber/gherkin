#include <gherkin/token.hpp>
#include <gherkin/types.hpp>

namespace gherkin {

template <
    typename Builder,
    typename Scanner,
    typename Matcher
>
struct parser_context
{
    Builder& builder;
    Scanner& scanner;
    Matcher& matcher;

    token_queue queue;
    strings errors;
    bool stop_at_first_error = false;

    bool has_token() const
    { return !queue.empty(); }

    token pop_token()
    {
        auto t = std::move(queue.front());
        queue.pop_front();

        return t;
    }

    token read_token()
    { return has_token() ? pop_token() : scanner.read(); }

    void push_tokens(const token_queue& q)
    { queue.insert(queue.end(), q.begin(), q.end()); }

    bool has_errors() const
    { return !errors.empty(); }

    void add_error(const std::string& e)
    { errors.push_back(e); }

    void add_error(const std::exception& e)
    { add_error(e.what()); }
};

}
