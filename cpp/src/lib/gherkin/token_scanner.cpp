#include <gherkin/token_scanner.hpp>

namespace gherkin {

token_scanner::token_scanner(const std::string& text)
: ip_(std::make_unique<std::istringstream>(text))
{}

token_scanner::token_scanner(const file& file)
: ip_(std::make_unique<std::ifstream>(file.path))
{}

token_scanner::~token_scanner()
{}

token
token_scanner::read()
{
    auto r = next_line();

    if (r.has_line) {
        $line =~ s/\r$//; # \n as well as \r\n are considered lines separators
        $line_token =
            Gherkin::Line->new(
                { line_text => $line, line_number => $line_number }
            );
    }
    return Gherkin::Token->new(line => $line_token, location => $location);
}

void
token_scanner::reset(input_ptr& ip)
{
    ip_ = std::move(ip);
    line_ = 0;
}

next_line_result
token_scanner::next_line()
{
    next_line_result r;

    if (ip_) {
        return r;
    }

    input >> r.text;
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
