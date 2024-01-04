#pragma once

#include <string>

#include <cucumber/gherkin/types.hpp>
#include <cucumber/gherkin/items.hpp>

namespace cucumber::gherkin {

class line
{
public:
    line();
    line(const std::string& line_text, std::size_t line_number);

    std::string get_rest_trimmed(std::size_t length) const;
    std::string get_keyword_trimmed(std::string_view kw) const;

    std::string_view get_line_text(
        std::size_t indent_to_remove = std::string::npos
    ) const;

    std::string_view line_text() const;

    std::size_t indent() const;

    bool is_empty() const;

    bool startswith(std::string_view prefix) const;
    bool startswith_title_keyword(const std::string& keyword) const;

    items table_cells() const;

    items tags() const;

private:
    std::string line_text_;
    std::size_t line_number_ = 0;
    std::size_t indent_ = 0;
    std::string trimmed_line_text_;
};

}
