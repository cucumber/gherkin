#ifndef CUCUMBER_GHERKIN_TOKEN_SCANNER_HPP
#define CUCUMBER_GHERKIN_TOKEN_SCANNER_HPP

#include "cucumber/gherkin/File.hpp"
#include "cucumber/gherkin/Token.hpp"
#include <cstddef>
#include <istream>
#include <memory>
#include <string>
#include <string_view>

namespace cucumber::gherkin
{

    struct NextLineResult
    {
        bool eof = true;
        std::string text;
    };

    class TokenScanner
    {
    public:
        TokenScanner() = default;
        TokenScanner(std::string_view data);
        TokenScanner(const File& file);

        virtual ~TokenScanner() = default;
        TokenScanner(const TokenScanner&) = delete;
        TokenScanner& operator=(const TokenScanner&) = delete;
        TokenScanner(TokenScanner&&) = delete;
        TokenScanner& operator=(TokenScanner&&) = delete;

        void Reset();
        void Reset(std::string_view data);
        void Reset(const File& file);

        Token Read();

    private:
        NextLineResult NextLine();

        std::istream& Input();

        using InputPtr = std::unique_ptr<std::istream>;

        std::size_t line = 0;
        InputPtr inputPtr;
    };

    using TokenScannerPtr = std::unique_ptr<TokenScanner>;

    template<typename... Args>
    TokenScannerPtr NewTokenScanner(Args&&... args)
    {
        return std::make_unique<TokenScanner>(std::forward<Args>(args)...);
    }

}

#endif
