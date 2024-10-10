from __future__ import annotations

from .ast_builder import AstBuilder
from .token import Token


class TokenFormatterBuilder(AstBuilder):
    _tokens: list[Token]

    def __init__(self) -> None:
        self.reset()
        self._tokens = []

    def reset(self) -> None:
        self._tokens = []

    def build(self, token: Token) -> None:
        self._tokens.append(token)

    def start_rule(self, rule_type: str) -> None:
        pass

    def end_rule(self, rule_type: str) -> None:
        pass

    def get_result(self) -> str:
        return "\n".join([self._format_token(token) for token in self._tokens])

    @staticmethod
    def _format_token(token: Token) -> str:
        if token.eof():
            return "EOF"

        return "".join(
            [
                "(",
                str(token.location["line"]),
                ":",
                str(token.location["column"]),
                ")",
                token.matched_type,
                ":",
                (
                    "".join(
                        [
                            "(",
                            (
                                token.matched_keyword_type
                                if token.matched_keyword_type
                                else ""
                            ),
                            ")",
                            token.matched_keyword,
                        ]
                    )
                    if token.matched_keyword
                    else ""
                ),
                "/",
                (token.matched_text if token.matched_text else ""),
                "/",
                ",".join(
                    [
                        str(item["column"]) + ":" + item["text"]
                        for item in token.matched_items
                    ]
                ),
            ]
        )
