#include <iostream>
#include <sstream>
#include <fstream>

#include <cucumber/gherkin/token_scanner.hpp>
#include <cucumber/gherkin/utils.hpp>

namespace cucumber::gherkin {

token_scanner::token_scanner()
{}

token_scanner::token_scanner(std::string_view data)
{ reset(data); }

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
        .line = cucumber::gherkin::line(r.text, line_),
        .location = {
            .line = line_
        }
    };
}

void
token_scanner::reset()
{
    line_ = 0;
}

void
token_scanner::reset(std::string_view data)
{
    reset();
    ip_ = std::make_unique<std::istringstream>(std::string(data));
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
    std::string line;

    if (ip_) {
        if (!input().eof()) {
            r.eof = !std::getline(input(), line);
            r.text = rstrip(line, re_pattern::cr);
        } else {
            ip_.reset();
        }
    }

    return r;
}

std::istream&
token_scanner::input()
{ return *ip_; }

}
