#pragma once

#include <string_view>

#include <cucumber/messages/source.hpp>

#include <gherkin/ast_builder.hpp>
#include <gherkin/token_scanner.hpp>
#include <gherkin/token_matcher.hpp>
#include <gherkin/parser_info.hpp>
#include <gherkin/parser_context.hpp>

namespace gherkin {

namespace cms = cucumber::messages;

template <
    typename Builder = ast_builder,
    typename Scanner = token_scanner,
    typename Matcher = token_matcher
>
class parser_base
{
public:
    using result_type = typename Builder::result_type;
    using context_type = parser_context<Builder, Scanner, Matcher>;

    parser_base(const parser_info& pi = {})
    : pi_{pi}
    {}

    virtual ~parser_base()
    {}

protected:
    void reset(std::string_view uri, std::string_view data)
    {
        builder_.reset(uri);
        scanner_.reset(data);
        matcher_.reset();
    }

    result_type parse(std::string_view uri, std::string_view data)
    {
        reset(uri, data);

        context_type context{
            .builder = builder_,
            .scanner = scanner_,
            .matcher = matcher_
        };

        parse(context);

        return get_result();
    }

    result_type get_result() const
    { return builder_.get_result(); }

    virtual void parse(context_type& context) = 0;

    parser_info pi_;
    Builder builder_;
    Scanner scanner_;
    Matcher matcher_;
};

}
