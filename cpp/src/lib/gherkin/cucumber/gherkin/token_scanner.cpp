#include "cucumber/gherkin/token_scanner.hpp"
#include "cucumber/gherkin/file.hpp"
#include "cucumber/gherkin/line.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/utils.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>

namespace cucumber::gherkin
{

    token_scanner::token_scanner()
    {}

    token_scanner::token_scanner(std::string_view data)
    {
        reset(data);
    }

    token_scanner::token_scanner(const file& file)
    {
        reset(file);
    }

    token_scanner::~token_scanner()
    {}

    token token_scanner::read()
    {
        auto line_result = next_line();

        line_++;

        return token{
            line_result.eof,
            cucumber::gherkin::line(line_result.text, line_),
            {},
            std::nullopt,
            std::nullopt,
            {},
            {},
            {},
            {},
            { line_ },
        };
    }

    void token_scanner::reset()
    {
        line_ = 0;
    }

    void token_scanner::reset(std::string_view data)
    {
        reset();
        ip_ = std::make_unique<std::istringstream>(std::string(data));
    }

    void token_scanner::reset(const file& file)
    {
        reset();
        ip_ = std::make_unique<std::ifstream>(file.path);
    }

    next_line_result token_scanner::next_line()
    {
        next_line_result result;
        std::string line;

        if (ip_)
        {
            if (!input().eof())
            {
                result.eof = !std::getline(input(), line);
                result.text = rstrip(line, re_pattern::cr);
            }
            else
            {
                ip_.reset();
            }
        }

        return result;
    }

    std::istream& token_scanner::input()
    {
        return *ip_;
    }

}
