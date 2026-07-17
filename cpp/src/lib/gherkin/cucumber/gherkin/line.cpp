#include "cucumber/gherkin/line.hpp"
#include "cucumber/gherkin/exceptions.hpp"
#include "cucumber/gherkin/items.hpp"
#include "cucumber/gherkin/regex.hpp"
#include "cucumber/gherkin/utils.hpp"
#include <algorithm>
#include <cstddef>
#include <regex>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace cucumber::gherkin
{
    namespace
    {
        using UnescapePair = std::pair<std::string, std::string>;
        using Unescapes = std::vector<UnescapePair>;

        const Unescapes lineUnescapes = { { "\\\\", "\\" }, { "\\|", "|" }, { "\\n", "\n" } };

        template<typename Callabble>
        void SplitTableCells(std::string_view row, Callabble&& cellCb)
        {
            auto wrow = ToWide(std::string(row));

            std::size_t col = 0;
            std::size_t startCol = col + 1;
            std::wstring cell;
            bool firstCell = true;
            auto current = wrow.begin();
            auto end = wrow.end();
            auto nextCh = [](auto& current, const auto& endIter)
            {
                return current != endIter ? *current++ : 0;
            };

            while (col < row.size())
            {
                auto character = nextCh(current, end);
                ++col;

                if (character == '|')
                {
                    if (firstCell)
                    {
                        firstCell = false;
                    }
                    else
                    {
                        std::forward<Callabble>(cellCb)(cell, startCol);
                    }

                    cell.clear();
                    startCol = col + 1;
                }
                else if (character == '\\')
                {
                    character = nextCh(current, end);
                    ++col;

                    if (character == 'n')
                    {
                        cell += '\n';
                    }
                    else
                    {
                        if (character != '|' && character != '\\')
                        {
                            cell += '\\';
                        }

                        cell += character;
                    }
                }
                else if (character)
                {
                    cell += character;
                }
            }
        }
    }

    Line::Line(const std::string& lineText, std::size_t lineNumber)
        : lineText(lineText)
        , lineNumber(lineNumber)
        , trimmedLineText(Lstrip(lineText))
    {
        indent = lineText.size() - trimmedLineText.size();
    }

    std::string Line::GetRestTrimmed(std::size_t length) const
    {
        auto pos = std::min(length, trimmedLineText.size());

        return Strip(trimmedLineText.substr(pos));
    }

    std::string Line::GetKeywordTrimmed(std::string_view keyword) const
    {
        // Keyword ends with ':'
        return GetRestTrimmed(keyword.size() + 1);
    }

    std::string_view Line::GetLineText(std::size_t indentToRemove) const
    {
        std::string_view view;

        if (indentToRemove == std::string::npos || indentToRemove > indent)
        {
            return trimmedLineText;
        }
        view = lineText;
        return view.substr(indentToRemove);
    }

    std::string_view Line::LineText() const
    {
        return lineText;
    }

    std::size_t Line::Indent() const
    {
        return indent;
    }

    bool Line::IsEmpty() const
    {
        return trimmedLineText.empty();
    }

    bool Line::Startswith(std::string_view prefix) const
    {
        return trimmedLineText.find(prefix) == 0;
    }

    bool Line::StartswithTitleKeyword(const std::string& keyword) const
    {
        return trimmedLineText.find(keyword + ":") == 0;
    }

    Items Line::TableCells() const
    {
        Items items;

        SplitTableCells(trimmedLineText,
            [&](const auto& cell, auto col)
            {
                using namespace std::literals;

                auto strippedCell = Lstrip(cell, RePattern::spacesNoNl);
                auto cellIndent = cell.size() - strippedCell.size();
                strippedCell = Rstrip(strippedCell, RePattern::spacesNoNl);

                Item tableItem{ col + indent + cellIndent, ToNarrow(strippedCell) };

                for (const auto& replacement : lineUnescapes)
                {
                    Subst(tableItem.text, replacement.first, replacement.second);
                }

                items.emplace_back(std::move(tableItem));
            });

        return items;
    }

    Items Line::Tags() const
    {
        Items tags;

        auto column = indent + 1;
        const auto itemsLine = Subst(trimmedLineText, "\\s+(?:#.*)?$", "");
        const auto items = Split("@", itemsLine);
        const std::regex noSpaces("^\\S+$");

        for (std::size_t i = 1; i < items.size(); ++i)
        {
            const auto originalItemSize = items[i].size();
            auto sitem = Strip(items[i]);

            if (sitem.empty())
            {
                continue;
            }

            if (!FullMatch(sitem, noSpaces))
            {
                throw ParserError("A tag may not contain whitespace", { lineNumber, column });
            }

            tags.emplace_back(Item{ column, "@" + sitem });

            column += originalItemSize + 1;
        }

        return tags;
    }

}
