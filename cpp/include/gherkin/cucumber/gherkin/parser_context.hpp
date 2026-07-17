#include "cucumber/gherkin/exceptions.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/token_matcher.hpp"
#include "cucumber/gherkin/token_scanner.hpp"
#include <cstddef>
#include <iostream>
#include <utility>

namespace cucumber::gherkin
{

    template<typename BuilderType>
    struct ParserContext
    {
        BuilderType& builder;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
        TokenScanner& scanner; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
        TokenMatcher& matcher; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)

        token_queue queue;
        parser_error_ptrs errorPointers;
        bool stopAtFirstError = false;
        std::size_t maxErrors = 10; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

        [[nodiscard]] bool HasToken() const
        {
            return !queue.empty();
        }

        Token PopToken()
        {
            auto frontToken = std::move(queue.front());
            queue.pop_front();

            return frontToken;
        }

        Token ReadToken()
        {
            return HasToken() ? PopToken() : scanner.Read();
        }

        void PushTokens(const token_queue& tokens)
        {
            queue.insert(queue.end(), tokens.begin(), tokens.end());
        }

        [[nodiscard]] bool HasErrors() const
        {
            return !errorPointers.empty();
        }

        void AddError(parser_error_ptr errorPointer)
        {
            for (const auto& existing : errorPointers)
            {
                if (existing->SameMessage(*errorPointer))
                {
                    return;
                }

                std::cerr << "not duplicate" << '\n';
            }

            errorPointers.emplace_back(std::move(errorPointer));

            if (errorPointers.size() > maxErrors)
            {
                throw CompositeParserError(errorPointers);
            }
        }
    };

}
