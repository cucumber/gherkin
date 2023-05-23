#include <utility>

#include <gherkin/line.hpp>
#include <gherkin/utils.hpp>
#include <gherkin/regex.hpp>

namespace gherkin {

using unescape_pair = std::pair<std::string_view, std::string_view>;
using unescapes = std::vector<unescape_pair>;

static const unescapes line_unescapes = {
    { "\\\\", "\\" },
    { "\\|", "|" },
    { "\\n", "\n" }
};

line::line()
{}

line::line(const std::string& line_text, std::size_t line_number)
: line_text_(line_text),
line_number_(line_number),
trimmed_line_text_(lstrip(line_text_))
{
    indent_ = line_text_.size() - trimmed_line_text_.size();
}

std::string_view
line::get_rest_trimmed(std::size_t length) const
{
    auto pos = std::min(length, trimmed_line_text_.size());
    std::string_view sv = trimmed_line_text_;

    return strip(sv.substr(pos));
}

std::string_view
line::get_line_text(std::size_t indent_to_remove) const
{
    std::string_view sv;

    if (indent_to_remove == std::string::npos || indent_to_remove > indent_) {
        return trimmed_line_text_;
    } else {
        sv = line_text_;
        return sv.substr(indent_to_remove);
    }
}

std::string_view
line::line_text() const
{ return line_text_; }

std::size_t
line::indent() const
{ return indent_; }

bool
line::is_empty() const
{ return trimmed_line_text_.empty(); }

bool
line::startswith(std::string_view prefix) const
{ return trimmed_line_text_.starts_with(prefix); }

bool
line::startswith_title_keyword(const std::string& keyword) const
{ return trimmed_line_text_.starts_with(keyword + ":"); }

items
line::table_cells() const
{
    items items;

    split_table_cells(
        strip(trimmed_line_text_),
        [&](const auto& cell, auto col) {
            auto stripped_cell = lstrip(cell);
            auto cell_indent = cell.size() - stripped_cell.size();
            stripped_cell = rstrip(stripped_cell);

            item i{
                .column = col + indent_ + cell_indent,
                .text = std::string(stripped_cell)
            };

            for (const auto& p : line_unescapes) {
                replace(i.text, p.first, p.second);
            }

            items.emplace_back(std::move(i));
        }
    );

    return items;
}

items
line::tags() const
{
    items tags;

    auto column = indent_ + 1;
    auto items_line = subst(trimmed_line_text_, "\\s+(?:#.*)?$", "");
    auto items = split("@", items_line);

    for (std::size_t i = 1; i < items.size(); ++i) {
        auto original_item = items[i];
        auto sitem = strip(items[i]);

        tags.emplace_back(item{
            .column = column,
            .text = "@" + std::string(sitem)
        });

        column += original_item.size() + 1;
    }

    return tags;
}

void
line::split_table_cells(
   std::string_view row,
   split_table_cell_function f
) const
{
    std::size_t col = 0;
    std::size_t start_col = col + 1;
    std::string cell;
    bool first_cell = true;
    auto it = row.begin();
    auto end = row.end();
    auto next_ch = [](auto& it, const auto& end) {
        return it != end ? *it++ : 0;
    };

    while (col < row.size()) {
        auto ch = next_ch(it, end);
        ++col;

        if (ch == '|') {
            if (first_cell) {
                first_cell = false;
            } else {
                f(cell, start_col);
            }

            cell.clear();
            start_col = col + 1;
        } else if (ch == '\\') {
            ch = next_ch(it, end);
            ++col;

            if (ch == 'n') {
                cell += '\n';
            } else {
                if (ch != '|' && ch != '\\') {
                    cell += '\\';
                }

                cell += ch;
            }
        } else if (ch) {
            cell += ch;
        } else {
            break;
        }
    }
}

}
