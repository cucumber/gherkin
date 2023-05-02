#include <sstream>
#include <fstream>

#include <gherkin/token_scanner.hpp>

namespace gherkin {

token_scanner::token_scanner(const std::string& text)
: ip_{std::make_unique<std::istringstream>(text)}
{}

token_scanner::token_scanner(const file& file)
: ip_{std::make_unique<std::ifstream>(file.path)}
{}

token_scanner::~token_scanner()
{}

token
token_scanner::read()
{
    auto r = next_line();

    line_++;

    return token{
        .line = gherkin::line(r.text, line_),
        .location = line_
    };
}

void
token_scanner::reset()
{
    line_ = 0;
}

next_line_result
token_scanner::next_line()
{
    next_line_result r;

    if (ip_) {
        return r;
    }

    input() >> r.text;
    line_++;

    r.has_line = !r.text.empty();

    if (!r.has_line) {
        ip_.reset();
    }

    return r;
}

std::istream&
token_scanner::input()
{ return *ip_; }

}
