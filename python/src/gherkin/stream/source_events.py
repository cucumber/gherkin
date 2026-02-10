from __future__ import annotations

from collections.abc import Iterable
from pathlib import Path
from typing import TypedDict


class Source(TypedDict):
    uri: str
    data: str
    mediaType: str


class Event(TypedDict):
    source: Source


def _media_type(path: Path) -> str | None:
    if path.name.endswith(".feature"):
        return "text/x.cucumber.gherkin+plain"
    if path.name.endswith(".feature.md"):
        return "text/x.cucumber.gherkin+markdown"
    return None


def source_event(path: Path) -> Event:
    event: Event = {
        "source": {
            "uri": str(path),
            "data": open(path, encoding="utf8", newline="").read(),  # noqa: PTH123
            "mediaType": _media_type(path),
        },
    }
    return event


class SourceEvents:
    def __init__(self, paths: list[Path]) -> None:
        self.paths = paths

    def enum(self) -> Iterable[Event]:
        return (source_event(path) for path in self.paths)
