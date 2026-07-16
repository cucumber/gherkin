#include "cucumber/gherkin/exceptions.hpp"
#include "cucumber/gherkin/join_utils.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/types.hpp"
#include <iostream>

namespace cucumber::gherkin
{

    template<typename Builder, typename Scanner, typename Matcher>
    struct parser_context
    {
        Builder& builder;
        Scanner& scanner;
        Matcher& matcher;

        token_queue queue;
        parser_error_ptrs error_pointers;
        bool stop_at_first_error = false;
        std::size_t max_errors = 10;

        bool has_token() const
        {
            return !queue.empty();
        }

        token pop_token()
        {
            auto front_token = std::move(queue.front());
            queue.pop_front();

            return front_token;
        }

        token read_token()
        {
            return has_token() ? pop_token() : scanner.read();
        }

        void push_tokens(const token_queue& tokens)
        {
            queue.insert(queue.end(), tokens.begin(), tokens.end());
        }

        bool has_errors() const
        {
            return !error_pointers.empty();
        }

        void add_error(parser_error_ptr error_pointer)
        {
            for (const auto& existing : error_pointers)
            {
                if (existing->same_message(*error_pointer))
                {
                    return;
                }

                std::cerr << "not duplicate" << std::endl;
            }

            error_pointers.emplace_back(std::move(error_pointer));

            if (error_pointers.size() > max_errors)
            {
                throw composite_parser_error(error_pointers);
            }
        }
    };

}
