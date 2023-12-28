#pragma once

#include <string_view>

#include <cucumber/messages/source.hpp>

#include <cucumber/gherkin/ast_builder.hpp>
#include <cucumber/gherkin/token_scanner.hpp>
#include <cucumber/gherkin/token_matcher.hpp>
#include <cucumber/gherkin/parser_context.hpp>
#include <cucumber/gherkin/id_generator.hpp>

namespace cucumber::gherkin {

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

    parser_base()
    {}

    parser_base(id_generator_ptr idp)
    : builder_(idp)
    {}

    virtual ~parser_base()
    {}

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

protected:
    void reset(std::string_view uri, std::string_view data)
    {
        builder_.reset(uri);
        scanner_.reset(data);
        matcher_.reset();
    }

    result_type get_result() const
    { return builder_.get_result(); }

    virtual void parse(context_type& context) = 0;

    Builder builder_;
    Scanner scanner_;
    Matcher matcher_;
};

}
