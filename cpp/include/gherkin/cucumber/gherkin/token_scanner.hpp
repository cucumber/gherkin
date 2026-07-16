#ifndef CUCUMBER_GHERKIN_TOKEN_SCANNER_HPP
#define CUCUMBER_GHERKIN_TOKEN_SCANNER_HPP

#include "cucumber/gherkin/file.hpp"
#include "cucumber/gherkin/line.hpp"
#include "cucumber/gherkin/token.hpp"
#include <memory>
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
        TokenScanner();
        TokenScanner(std::string_view data);
        TokenScanner(const File& File);

        virtual ~TokenScanner();

        void reset();
        void reset(std::string_view data);
        void reset(const File& File);

        Token read();

    private:
        NextLineResult next_line();

        std::istream& input();

        using input_ptr = std::unique_ptr<std::istream>;

        std::size_t line_ = 0;
        input_ptr ip_;
    };

    using token_scanner_ptr = std::unique_ptr<TokenScanner>;

    template<typename... Args>
    token_scanner_ptr new_token_scanner(Args&&... args)
    {
        return std::make_unique<TokenScanner>(std::forward<Args>(args)...);
    }

}

#endif
