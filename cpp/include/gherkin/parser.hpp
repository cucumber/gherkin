#include <gherkin/basic_parser.hpp>
#include <gherkin/file.hpp>
#include <gherkin/utils.hpp>
#include <gherkin/msg_types.hpp>

namespace gherkin {

template <
    typename Builder = ast_builder
>
class parser : public basic_parser<Builder>
{
public:
    using parent = basic_parser<Builder>;
    using result_type = typename parent::result_type;

    parser(const parser_info& pi = {})
    : parent(pi)
    {}

    result_type parse(const file& file)
    {
        return
            parse(cms::source{
                .uri = file.path,
                .data = slurp(file.path)
            });
    }

    result_type parse(const cms::source& source)
    { return parent::parse(source.uri, source.data); }

private:
};

}
