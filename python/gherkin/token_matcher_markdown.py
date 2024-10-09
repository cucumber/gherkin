from __future__ import annotations

import re
from collections.abc import Iterable

from .gherkin_line import Cell
from .token import Token
from .token_matcher import TokenMatcher, MatchedItems

KEYWORD_PREFIX_BULLET = "^(\\s*[*+-]\\s*)"
KEYWORD_PREFIX_HEADER = "^(#{1,6}\\s)"


class GherkinInMarkdownTokenMatcher(TokenMatcher):

    def __init__(self, dialect_name: str = "en") -> None:
        super().__init__(dialect_name)

    def reset(self) -> None:
        super().reset()
        self.matched_feature_line = False

    def match_FeatureLine(self, token: Token) -> bool:

        if self.matched_feature_line:
            self._set_token_matched(token, None)

        # We first try to match "# Feature: blah"
        result = self._match_title_line(
            KEYWORD_PREFIX_HEADER,
            self.dialect.feature_keywords,
            ":",
            token,
            "FeatureLine",
        )
        # If we didn't match "# Feature: blah", we still match this line
        # as a FeatureLine.
        # The reason for this is that users may not want to be constrained by having this as their fist line.

        if not result:
            self._set_token_matched(token, "FeatureLine", token.line.get_line_text())
        self.matched_feature_line = result
        return result

    def match_RuleLine(self, token: Token) -> bool:
        return self._match_title_line(
            KEYWORD_PREFIX_HEADER, self.dialect.rule_keywords, ":", token, "RuleLine"
        )

    def match_ScenarioLine(self, token: Token) -> bool:
        return self._match_title_line(
            KEYWORD_PREFIX_HEADER,
            self.dialect.scenario_keywords,
            ":",
            token,
            "ScenarioLine",
        ) or self._match_title_line(
            KEYWORD_PREFIX_HEADER,
            self.dialect.scenario_outline_keywords,
            ":",
            token,
            "ScenarioLine",
        )

    def match_BackgroundLine(self, token: Token) -> bool:
        return self._match_title_line(
            KEYWORD_PREFIX_HEADER,
            self.dialect.background_keywords,
            ":",
            token,
            "BackgroundLine",
        )

    def match_ExamplesLine(self, token: Token) -> bool:
        return self._match_title_line(
            KEYWORD_PREFIX_HEADER,
            self.dialect.examples_keywords,
            ":",
            token,
            "ExamplesLine",
        )

    def match_TableRow(self, token: Token) -> bool:
        # Gherkin tables must be indented 2-5 spaces to be distinguishable from non-Gherkin tables

        if re.match("^\\s\\s\\s?\\s?\\s?\\|", token.line.get_line_text(0)):
            table_cells = token.line.table_cells
            if self._is_gfm_table_separator(table_cells):
                return False

            self._set_token_matched(
                token, "TableRow", keyword="|", items=token.line.table_cells
            )

            return True
        return False

    def _is_gfm_table_separator(self, table_cells: list[Cell]) -> bool:
        text_of_table_cells = map(lambda x: x["text"], table_cells)
        separator_values = list(
            filter(lambda x: re.match("^:?-+:?$", x), text_of_table_cells)
        )
        return len(separator_values) > 0

    def match_StepLine(self, token: Token) -> bool:
        nonStarStepKeywords = (
            self.dialect.given_keywords
            + self.dialect.when_keywords
            + self.dialect.then_keywords
            + self.dialect.and_keywords
            + self.dialect.but_keywords
        )
        return self._match_title_line(
            KEYWORD_PREFIX_BULLET, nonStarStepKeywords, "", token, "StepLine"
        )

    def match_Comment(self, token: Token) -> bool:
        if token.line.startswith("|"):
            table_cells = token.line.table_cells
            if self._is_gfm_table_separator(table_cells):
                return True
        return self._set_token_matched(token, None, False)

    def match_Empty(self, token: Token) -> bool:

        result = False
        if token.line.is_empty():
            result = True
        if (
            not self.match_TagLine(token)
            and not self.match_FeatureLine(token)
            and not self.match_ScenarioLine(token)
            and not self.match_BackgroundLine(token)
            and not self.match_ExamplesLine(token)
            and not self.match_RuleLine(token)
            and not self.match_TableRow(token)
            and not self.match_Comment(token)
            and not self.match_Language(token)
            and not self.match_DocStringSeparator(token)
            and not self.match_EOF(token)
            and not self.match_StepLine(token)
        ):
            # neutered
            result = True

        if result:
            self._set_token_matched(token, "Empty", indent=0)
            return result
        return False

    # We've made a deliberate choice not to support `# language: [ISO 639-1]` headers or similar
    # in Markdown. Users should specify a language globally.
    def match_Language(self, token: Token) -> bool:
        if not token:
            raise ValueError("no token")
        return False

    def match_TagLine(self, token: Token) -> bool:
        tags: list[MatchedItems] = []
        matching_tags = re.finditer("`(@[^`]+)`", token.line.get_line_text())
        idx = 0
        for match in matching_tags:
            tags.append(
                {
                    "column": token.line.indent + match.start(idx) + 2,
                    "text": match.group(1),
                }
            )

        if len(tags) == 0:
            return False

        self._set_token_matched(token, "TagLine", items=tags)
        return True

    def match_DocStringSeparator(self, token: Token) -> bool:
        if not self._active_doc_string_separator:
            # open
            return (
                self._match_DocStringSeparator(token, '"""', True)
                or self._match_DocStringSeparator(token, "````", True)
                or self._match_DocStringSeparator(token, "```", True)
            )
        else:
            # close
            return self._match_DocStringSeparator(
                token, self._active_doc_string_separator, False
            )

    @staticmethod
    def _default_docstring_content_type() -> str:
        return ""

    def _match_title_line(
        self,
        prefix: str,
        keywords: Iterable[str],
        keywordSuffix: str,
        token: Token,
        token_type: str,
    ) -> bool:
        keywords_or_list = "|".join(map(lambda x: re.escape(x), keywords))
        match = re.search(
            f"{prefix}({keywords_or_list}){keywordSuffix}(.*)",
            token.line.get_line_text(),
        )
        indent = token.line.indent

        if match:
            matchedKeyword = match.group(2)
            indent += len(match.group(1))
            self._set_token_matched(
                token, token_type, match.group(3).strip(), matchedKeyword, indent=indent
            )
            return True
        return False
