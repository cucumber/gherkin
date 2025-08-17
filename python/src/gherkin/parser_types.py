from __future__ import annotations

from typing import TypedDict
from typing_extensions import NotRequired


class Location(TypedDict):
    line: int
    column: NotRequired[int]


class Comment(TypedDict):
    location: Location
    text: str


class Tag(TypedDict):
    id: str
    location: Location
    name: str


class Cell(TypedDict):
    location: Location
    value: str


class TableRow(TypedDict):
    id: str
    location: Location
    cells: list[Cell]


class DataTable(TypedDict):
    location: Location
    rows: list[TableRow]


class DocString(TypedDict):
    location: Location
    content: str
    delimiter: str
    mediaType: NotRequired[str]


class Step(TypedDict):
    id: str
    location: Location
    keyword: str
    text: str
    keywordType: str
    dataTable: NotRequired[DataTable]
    docString: NotRequired[DocString]


class Background(TypedDict):
    id: str
    location: Location
    keyword: str
    name: str
    description: str
    steps: list[Step]


class Examples(TypedDict):
    id: str
    location: Location
    tags: list[Tag]
    keyword: str
    name: str
    description: str
    tableHeader: TableRow
    tableBody: list[TableRow]


class Scenario(TypedDict):
    id: str
    location: Location
    tags: list[Tag]
    keyword: str
    name: str
    description: str
    steps: list[Step]
    examples: list[Examples]


class Envelope(TypedDict):
    pass


class Rule(TypedDict):
    id: str
    location: Location
    tags: list[Tag]
    keyword: str
    name: str
    description: str
    children: list[Envelope]


class BackgroundEnvelope(Envelope):
    background: Background


class ScenarioEnvelope(Envelope):
    scenario: Scenario


class RuleEnvelope(Envelope):
    rule: Rule


class Feature(TypedDict):
    location: Location
    tags: list[Tag]
    language: str
    keyword: str
    name: str
    description: str
    children: list[Envelope]


class GherkinDocument(TypedDict):
    feature: Feature
    comments: list[Comment]
