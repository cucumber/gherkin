#include <utility>
#include <string_view>

#include <dbj/meta_converter.hpp>

#include <gherkin/line.hpp>
#include <gherkin/utils.hpp>
#include <gherkin/regex.hpp>

namespace gherkin {

using unescape_pair = std::pair<std::string, std::string>;
using unescapes = std::vector<unescape_pair>;

static const unescapes line_unescapes = {
    { "\\\\", "\\" },
    { "\\|", "|" },
    { "\\n", "\n" }
};

template <typename Callabble>
void
split_table_cells(std::string_view svrow, Callabble&& cell_cb)
{
    dbj::wchar_range_to_string to_wstring{};

    auto wrow = to_wstring(svrow);
    wrow = std::regex_replace(wrow, std::wregex(L"^\\s+"), std::wstring{});
    wrow = std::regex_replace(wrow, std::wregex(L"\\s+$"), std::wstring{});

    std::size_t col = 0;
    std::size_t start_col = col + 1;
    std::wstring cell;
    bool first_cell = true;
    auto it = wrow.begin();
    auto end = wrow.end();
    auto next_ch = [](auto& it, const auto& end) {
        return it != end ? *it++ : 0;
    };

    while (col < wrow.size()) {
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
line_number_(line_number)
{
    trimmed_line_text_ = std::regex_replace(
        line_text_, std::regex("^\\s+"), std::string{}
    );

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
    dbj::char_range_to_string to_string{};
    dbj::wchar_range_to_string to_wstring{};

    auto spaces = to_wstring("[ \t\v\f\r\u0085\u00A0]*");
    std::wstring lspaces = L"^"; lspaces += spaces;
    std::wregex lstrip(lspaces);
    std::wstring rspaces = spaces; rspaces += L"$";
    std::wregex rstrip(rspaces);
    std::wstring empty{};

    split_table_cells(
        trimmed_line_text_,
        [&](const auto& cell, auto col) {
            using namespace std::literals;

            auto stripped_cell = std::regex_replace(cell, lstrip, empty);
            auto cell_indent = cell.size() - stripped_cell.size();
            stripped_cell = std::regex_replace(stripped_cell, rstrip, empty);

            item i{
                .column = col + indent_ + cell_indent,
                .text = to_string(stripped_cell)
            };

            for (const auto& p : line_unescapes) {
                std::regex_replace(i.text, std::regex(p.first), p.second);
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

}
