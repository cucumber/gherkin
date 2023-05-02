#include <gherkin/line.hpp>
#include <gherkin/utils.hpp>

namespace gherkin {

line::line()
{}

line::line(const std::string& line_text, std::size_t line_number)
: line_text_(line_text),
line_number_(line_number),
trimmed_line_text_(lstrip(line_text_)),
indent_(line_text_.size() - trimmed_line_text_.size())
{}

std::string_view
line::get_rest_trimmed(std::size_t length) const
{
    auto pos = std::min(length, trimmed_line_text_.size());

    return strip(trimmed_line_text_.substr(pos));
}

std::string_view
line::get_line_text(std::size_t indent_to_remove) const
{
    if (indent_to_remove == std::string::npos || indent_to_remove > indent_) {
        return trimmed_line_text_;
    } else {
        return line_text_.substr(indent_to_remove);
    }
}

bool
line::is_empty() const
{ return trimmed_line_text_.empty(); }

bool
line::startswith(std::string_view prefix) const
{ return trimmed_line_text_.startswith(prefix); }

bool
line::startswith_title_keyword(std::string_view keyword) const
{ return trimmed_line_text_.startswith(keyword + ":"); }

items
line::table_cells() const
{
    items items;

    return items;
}

items
line::tags() const
{
    items items;

    return items;
}

}
