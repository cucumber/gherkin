#include <cucumber/gherkin/token.hpp>
#include <cucumber/gherkin/types.hpp>
#include <cucumber/gherkin/exceptions.hpp>
#include <cucumber/gherkin/join_utils.hpp>

namespace cucumber::gherkin {

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
    parser_error_ptrs eptrs;
    bool stop_at_first_error = false;
    std::size_t max_errors = 10;

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
    { return !eptrs.empty(); }

    void add_error(parser_error_ptr ep)
    {
        for (const auto& p : eptrs) {
            if (p->same_message(*ep)) {
                return;
            }

            std::cerr << "not duplicate" << std::endl;
        }

        eptrs.emplace_back(std::move(ep));

        if (eptrs.size() > max_errors) {
            throw composite_parser_error(eptrs);
        }
    }
};

}
