#include <utility>
#include <string_view>

#include <cucumber/gherkin/line.hpp>
#include <cucumber/gherkin/utils.hpp>
#include <cucumber/gherkin/regex.hpp>
#include <cucumber/gherkin/exceptions.hpp>

namespace cucumber::gherkin {

using unescape_pair = std::pair<std::string, std::string>;
using unescapes = std::vector<unescape_pair>;

static const unescapes line_unescapes = {
    { "\\\\", "\\" },
    { "\\|", "|" },
    { "\\n", "\n" }
};

template <typename Callabble>
void
split_table_cells(std::string_view row, Callabble&& cell_cb)
{
    auto wrow = to_wide(std::string(row));

    std::size_t col = 0;
    std::size_t start_col = col + 1;
    std::wstring cell;
    bool first_cell = true;
    auto it = wrow.begin();
    auto end = wrow.end();
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
                cell_cb(cell, start_col);
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
        }
    }
}

line::line()
{}

line::line(const std::string& line_text, std::size_t line_number)
: line_text_(line_text),
line_number_(line_number),
trimmed_line_text_(lstrip(line_text_))
{
    indent_ = line_text_.size() - trimmed_line_text_.size();
}

std::string
line::get_rest_trimmed(std::size_t length) const
{
    auto pos = std::min(length, trimmed_line_text_.size());

    return strip(trimmed_line_text_.substr(pos));
}

std::string
line::get_keyword_trimmed(std::string_view kw) const
{
    // Keyword ends with ':'
    return get_rest_trimmed(kw.size() + 1);
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
{ return trimmed_line_text_.find(prefix) == 0; }

bool
line::startswith_title_keyword(const std::string& keyword) const
{ return trimmed_line_text_.find(keyword + ":") == 0; }

items
line::table_cells() const
{
    items items;

    split_table_cells(
        trimmed_line_text_,
        [&](const auto& cell, auto col) {
            using namespace std::literals;

            auto stripped_cell = lstrip(cell, re_pattern::spaces_no_nl);
            auto cell_indent = cell.size() - stripped_cell.size();
            stripped_cell = rstrip(stripped_cell, re_pattern::spaces_no_nl);

            item i{
                .column = col + indent_ + cell_indent,
                .text = to_narrow(stripped_cell)
            };

            for (const auto& p : line_unescapes) {
                subst(i.text, p.first, p.second);
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
    std::regex no_spaces("^\\S+$");

    for (std::size_t i = 1; i < items.size(); ++i) {
        auto original_item = items[i];
        auto sitem = strip(items[i]);

        if (sitem.empty()) {
            continue;
        }

        if (!full_match(sitem, no_spaces)) {
            throw
                parser_error(
                    "A tag may not contain whitespace",
                    { .line = line_number_, .column = column }
                );
        }

        tags.emplace_back(item{
            .column = column,
            .text = "@" + sitem
        });

        column += original_item.size() + 1;
    }

    return tags;
}

}
