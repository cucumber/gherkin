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

    TokenScanner::TokenScanner()
    {}

    TokenScanner::TokenScanner(std::string_view data)
    {
        reset(data);
    }

    TokenScanner::TokenScanner(const File& File)
    {
        reset(File);
    }

    TokenScanner::~TokenScanner()
    {}

    Token TokenScanner::read()
    {
        auto line_result = next_line();

        line_++;

        return Token{
            line_result.eof,
            cucumber::gherkin::Line(line_result.text, line_),
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

    void TokenScanner::reset()
    {
        line_ = 0;
    }

    void TokenScanner::reset(std::string_view data)
    {
        reset();
        ip_ = std::make_unique<std::istringstream>(std::string(data));
    }

    void TokenScanner::reset(const File& File)
    {
        reset();
        ip_ = std::make_unique<std::ifstream>(File.path);
    }

    NextLineResult TokenScanner::next_line()
    {
        NextLineResult result;
        std::string Line;

        if (ip_)
        {
            if (!input().eof())
            {
                result.eof = !std::getline(input(), Line);
                result.text = rstrip(Line, RePattern::cr);
            }
            else
            {
                ip_.reset();
            }
        }

        return result;
    }

    std::istream& TokenScanner::input()
    {
        return *ip_;
    }

}
