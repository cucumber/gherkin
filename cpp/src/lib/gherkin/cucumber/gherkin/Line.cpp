#include "cucumber/gherkin/Line.hpp"
#include "cucumber/gherkin/Exceptions.hpp"
#include "cucumber/gherkin/Items.hpp"
#include "cucumber/gherkin/Regex.hpp"
#include "cucumber/gherkin/Utils.hpp"
#include <algorithm>
#include <cstddef>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace cucumber::gherkin
{
    namespace
    {
        template<typename Callabble>
        void SplitTableCells(std::string_view row, Callabble&& cellCb)
        {
            auto wrow = ToWide(row);

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
                auto strippedCell = detail::TrimView<wchar_t, true>(cell, RePattern::spacesNoNl);
                auto cellIndent = cell.size() - strippedCell.size();
                strippedCell = detail::TrimView<wchar_t, false>(strippedCell, RePattern::spacesNoNl);

                items.emplace_back(Item{ col + indent + cellIndent, ToNarrow(strippedCell) });
            });

        return items;
    }

    Items Line::Tags() const
    {
        Items tags;

        auto column = indent + 1;
        static const Regex trailingComment("\\s+(?:#.*)?$");
        static const Regex tagSeparator("@");
        static const Regex noSpaces("^\\S+$");
        const auto itemsLine = trailingComment.Replace(trimmedLineText, "");
        const auto items = tagSeparator.Split(itemsLine);

        for (std::size_t i = 1; i < items.size(); ++i)
        {
            const auto originalItemSize = items.at(i).size();
            auto sitem = Strip(items.at(i));

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
