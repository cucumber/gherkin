from typing import TypedDict
from typing_extensions import NotRequired

from gherkin.gherkin_line import GherkinLine

class Location(TypedDict):
    line: int
    column: NotRequired[int]

class Token:
    def __init__(self, gherkin_line: GherkinLine, location: Location):
        self.line = gherkin_line
        self.location = location

    def eof(self) -> bool:
        return not self.line

    def detach(self) -> None:
        pass  # TODO: detach line - is this needed?

    def token_value(self) -> str:
        return "EOF" if self.eof() else self.line.get_line_text()
