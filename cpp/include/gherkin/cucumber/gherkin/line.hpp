#ifndef CUCUMBER_GHERKIN_LINE_HPP
#define CUCUMBER_GHERKIN_LINE_HPP

#include "cucumber/gherkin/items.hpp"
#include <cstddef>
#include <string>
#include <string_view>

namespace cucumber::gherkin
{

    class Line
    {
    public:
        Line();
        Line(const std::string& lineText, std::size_t lineNumber);

        [[nodiscard]] std::string GetRestTrimmed(std::size_t length) const;
        [[nodiscard]] std::string GetKeywordTrimmed(std::string_view keyword) const;

        [[nodiscard]] std::string_view GetLineText(std::size_t indentToRemove = std::string::npos) const;

        [[nodiscard]] std::string_view LineText() const;

        [[nodiscard]] std::size_t Indent() const;

        [[nodiscard]] bool IsEmpty() const;

        [[nodiscard]] bool Startswith(std::string_view prefix) const;
        [[nodiscard]] bool StartswithTitleKeyword(const std::string& keyword) const;

        [[nodiscard]] Items TableCells() const;

        [[nodiscard]] Items Tags() const;

    private:
        std::string lineText;
        std::size_t lineNumber = 0;
        std::size_t indent = 0;
        std::string trimmedLineText;
    };

}

#endif
