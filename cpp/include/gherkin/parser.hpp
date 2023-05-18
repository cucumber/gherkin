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
    using parent::basic_parser;
    using result_type = typename parent::result_type;

    envelopes parse(const file& file)
    {
        return
            parse(cms::source{
                .uri = file.path,
                .data = slurp(file.path)
            });
    }

    // TODO: add more of these with proper move semantics...
    result_type parse(const std::string& uri, const std::string& data)
    {
        return
            parse(cms::source{
                .uri = uri,
                .data = data
            });
    }

private:
};


}
