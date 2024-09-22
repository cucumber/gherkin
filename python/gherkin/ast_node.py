from __future__ import annotations

from collections import defaultdict
from typing import TypeVar

from .token import Token

T = TypeVar("T")


class AstNode:

    def __init__(self, rule_type: str) -> None:
        self.rule_type = rule_type
        self._sub_items: defaultdict[str, list[object]] = defaultdict(list)

    def add(self, rule_type: str | None, obj: object) -> None:
        self._sub_items[rule_type].append(obj)

    def get_single(self, rule_type: str, default_value: object = None) -> object:
        return (
            self._sub_items[rule_type][0]
            if self._sub_items[rule_type]
            else default_value
        )

    def get_items(self, rule_type: str) -> list[object]:
        return self._sub_items[rule_type]

    def get_token(self, token_type: str) -> Token:
        return self.get_single(token_type)

    def get_tokens(self, token_type: str) -> list[Token]:
        return self._sub_items[token_type]
