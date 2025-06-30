from __future__ import annotations

import re

from collections.abc import Generator
from typing import TypedDict

from .errors import ParserException
from .parser_types import Location


class Cell(TypedDict):
    column: int
    text: str


class GherkinLine:
    def __init__(self, line_text: str, line_number: int) -> None:
        self._line_text = line_text
        self._line_number = line_number
        self._trimmed_line_text = line_text.lstrip()
        self.indent = len(line_text) - len(self._trimmed_line_text)

    def get_rest_trimmed(self, length: int) -> str:
        return self._trimmed_line_text[length:].strip()

    def get_line_text(self, indent_to_remove: int = -1) -> str:
        if indent_to_remove < 0 or indent_to_remove > self.indent:
            return self._trimmed_line_text
        else:
            return self._line_text[indent_to_remove:]

    def is_empty(self) -> bool:
        return not self._trimmed_line_text

    def startswith(self, prefix: str) -> bool:
        return self._trimmed_line_text.startswith(prefix)

    def startswith_title_keyword(self, keyword: str) -> bool:
        return self._trimmed_line_text.startswith(keyword + ":")

    @property
    def table_cells(self) -> list[Cell]:
        cells: list[Cell] = []
        for cell, col in self.split_table_cells(self._trimmed_line_text.strip()):
            lstripped_cell = re.sub(r"^[^\S\n]*", "", cell, flags=re.U)
            cell_indent = len(cell) - len(lstripped_cell)
            cells.append(
                {
                    "column": col + self.indent + cell_indent,
                    "text": re.sub(r"[^\S\n]*$", "", lstripped_cell, flags=re.U),
                }
            )
        return cells

    @staticmethod
    def split_table_cells(row: str) -> Generator[tuple[str, int]]:
        """
        An iterator returning all the table cells in a row with their positions,
        accounting for escaping.
        """

        row_iter = iter(row)
        col = 0
        start_col = col + 1
        cell = ""
        first_cell = True
        while True:
            char = next(row_iter, None)
            col += 1
            if char == "|":
                if first_cell:
                    # First cell (content before the first |) is skipped
                    first_cell = False
                else:
                    yield cell, start_col
                cell = ""
                start_col = col + 1
            elif char == "\\":
                char = next(row_iter, "")
                col += 1
                if char == "n":
                    cell += "\n"
                else:
                    if char not in ["|", "\\"]:
                        cell += "\\"
                    cell += char
            elif char:
                cell += char
            else:
                break
        # Last cell (content after the last |) is skipped

    @property
    def tags(self) -> list[Cell]:
        column = self.indent + 1
        uncommented_line = re.split(
            r"\s#", self._trimmed_line_text.strip(), maxsplit=2
        )[0]
        items = uncommented_line.strip().split("@")
        tags: list[Cell] = []
        for item in items[1:]:
            tag_value = "@" + item.strip()
            if re.search(r"[^\S+]", tag_value) is not None:
                location: Location = {"line": self._line_number, "column": column}
                raise ParserException("A tag may not contain whitespace", location)

            tags.append({"column": column, "text": tag_value})
            column += len(item) + 1
        return tags
