from __future__ import annotations

from collections.abc import Iterable
from typing import TypedDict


class Source(TypedDict):
    uri: str
    data: str
    mediaType: str


class Event(TypedDict):
    source: Source


def source_event(path: str) -> Event:
    event: Event = {
        "source": {
            "uri": path,
            "data": open(path, encoding="utf8", newline="").read(),
            "mediaType": "text/x.cucumber.gherkin+plain",
        }
    }
    return event


class SourceEvents:
    def __init__(self, paths: list[str]) -> None:
        self.paths = paths

    def enum(self) -> Iterable[Event]:
        return map(source_event, self.paths)
