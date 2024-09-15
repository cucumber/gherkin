from typing import TypedDict


class Location(TypedDict):
    line: int
    column: int

class Comment(TypedDict):
    location: Location
    text: str

class Tag(TypedDict):
    id: str
    location: Location
    name: str

class Step(TypedDict):
    id: str
    location: Location
    keyword: str
    text: str
    keywordType: str

class Background(TypedDict):
    id: str
    location: Location
    keyword: str
    name: str
    description: str
    steps: list[Step]

class Cell(TypedDict):
    location: Location
    value: str

class TableRow(TypedDict):
    id: str
    location: Location
    cells: list[Cell]


class Example(TypedDict):
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
    examples: list[Example]

class Container(TypedDict):
    pass

class BackgroundContainer(Container):
    background: Background

class ScenarioContainer(Container):
    scenario: Scenario

class Feature(TypedDict):
    location: Location
    tags: list[object]
    language: str
    keyword: str
    name: str
    description: str
    children: list[object]

class GherkinDocument(TypedDict):
    feature: Feature
    comments: list[Comment]
