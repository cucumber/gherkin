from __future__ import annotations

import os
import json
from typing import TypedDict

from typing_extensions import Self

DIALECT_FILE_PATH = os.path.join(
    os.path.dirname(__file__),
    "gherkin-languages.json",
)

DialectSpec = TypedDict(
    "DialectSpec",
    {
        "and": list[str],
        "background": list[str],
        "but": list[str],
        "examples": list[str],
        "feature": list[str],
        "given": list[str],
        "rule": list[str],
        "scenario": list[str],
        "scenarioOutline": list[str],
        "then": list[str],
        "when": list[str],
    },
)

with open(DIALECT_FILE_PATH, encoding="utf-8") as file:
    DIALECTS: dict[str, DialectSpec] = json.load(file)


class Dialect:

    @classmethod
    def for_name(cls, name: str) -> Self | None:
        return cls(DIALECTS[name]) if name in DIALECTS else None

    def __init__(self, spec: DialectSpec) -> None:
        self.spec = spec

    @property
    def feature_keywords(self) -> list[str]:
        return self.spec["feature"]

    @property
    def rule_keywords(self) -> list[str]:
        return self.spec["rule"]

    @property
    def scenario_keywords(self) -> list[str]:
        return self.spec["scenario"]

    @property
    def scenario_outline_keywords(self) -> list[str]:
        return self.spec["scenarioOutline"]

    @property
    def background_keywords(self) -> list[str]:
        return self.spec["background"]

    @property
    def examples_keywords(self) -> list[str]:
        return self.spec["examples"]

    @property
    def given_keywords(self) -> list[str]:
        return self.spec["given"]

    @property
    def when_keywords(self) -> list[str]:
        return self.spec["when"]

    @property
    def then_keywords(self) -> list[str]:
        return self.spec["then"]

    @property
    def and_keywords(self) -> list[str]:
        return self.spec["and"]

    @property
    def but_keywords(self) -> list[str]:
        return self.spec["but"]
