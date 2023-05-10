#include <sstream>
#include <fstream>

#include <gherkin/token_scanner.hpp>

namespace gherkin {

token_scanner::token_scanner()
{}

token_scanner::token_scanner(const std::string& text)
{ reset(text); }

token_scanner::token_scanner(const file& file)
{ reset(file); }

token_scanner::~token_scanner()
{}

token
token_scanner::read()
{
    auto r = next_line();

    line_++;

    return token{
        .eof = r.eof,
        .line = gherkin::line(r.text, line_),
        .location = line_
    };
}

void
token_scanner::reset()
{
    line_ = 0;
}

void
token_scanner::reset(const std::string& text)
{
    reset();
    ip_ = std::make_unique<std::istringstream>(text);
}

void
token_scanner::reset(const file& file)
{
    reset();
    ip_ = std::make_unique<std::ifstream>(file.path);
}


next_line_result
token_scanner::next_line()
{
    next_line_result r;

    if (!ip_) {
        return r;
    }

    std::getline(input(), r.text);

    r.eof = input().eof();

    if (r.eof) {
        ip_.reset();
    }

    return r;
}

std::istream&
token_scanner::input()
{ return *ip_; }

}
