from __future__ import annotations

import contextlib
import io
import os
from pathlib import Path

from .gherkin_line import GherkinLine
from .parser_types import Location
from .token import Token


class TokenScanner:
    """
    The scanner reads a gherkin doc (typically read from a `.feature` file) and creates a token for
    each line.

    The tokens are passed to the parser, which outputs an AST (Abstract Syntax Tree).

    If the scanner sees a `#` language header, it will reconfigure itself dynamically to look for
    Gherkin keywords for the associated language. The keywords are defined in
    :file:`gherkin-languages.json`.
    """

    def __init__(self, path_or_str: str | Path) -> None:
        if isinstance(path_or_str, Path):
            self.io = open(path_or_str, encoding="utf8")
        else:
            self.io = io.StringIO(path_or_str)
        self.line_number = 0

    def read(self) -> Token:
        self.line_number += 1
        location: Location = {"line": self.line_number}
        line = self.io.readline()
        return Token((GherkinLine(line, self.line_number) if line else line), location)

    def __del__(self) -> None:
        # close file descriptor if it's still open
        with contextlib.suppress(AttributeError):
            self.io.close()
