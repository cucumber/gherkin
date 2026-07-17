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

    TokenScanner::TokenScanner() = default;

    TokenScanner::TokenScanner(std::string_view data)
    {
        Reset(data);
    }

    TokenScanner::TokenScanner(const File& file)
    {
        Reset(file);
    }

    TokenScanner::~TokenScanner() = default;

    Token TokenScanner::Read()
    {
        auto lineResult = NextLine();

        line++;

        return Token{
            lineResult.eof,
            cucumber::gherkin::Line(lineResult.text, line),
            {},
            std::nullopt,
            std::nullopt,
            {},
            {},
            {},
            {},
            { line },
        };
    }

    void TokenScanner::Reset()
    {
        line = 0;
    }

    void TokenScanner::Reset(std::string_view data)
    {
        Reset();
        ip = std::make_unique<std::istringstream>(std::string(data));
    }

    void TokenScanner::Reset(const File& file)
    {
        Reset();
        ip = std::make_unique<std::ifstream>(file.path);
    }

    NextLineResult TokenScanner::NextLine()
    {
        NextLineResult result;
        std::string line;

        if (ip)
        {
            if (!Input().eof())
            {
                result.eof = !std::getline(Input(), line);
                result.text = Rstrip(line, RePattern::CR);
            }
            else
            {
                ip.reset();
            }
        }

        return result;
    }

    std::istream& TokenScanner::Input()
    {
        return *ip;
    }

}
