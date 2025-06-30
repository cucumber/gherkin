from __future__ import annotations

from typing import TypedDict, cast, TypeVar, Union

from .ast_node import AstNode
from .errors import AstBuilderException
from .parser_types import (
    GherkinDocument,
    Tag,
    TableRow,
    Cell,
    Step,
    DocString,
    Scenario,
    Background,
    DataTable,
    Examples,
    Rule,
    Feature,
)
from .stream.id_generator import IdGenerator
from .token import Location, Token

T = TypeVar("T")


class Comment(TypedDict):
    location: Location
    text: str


class AstBuilder:
    id_generator: IdGenerator
    stack: list[AstNode]
    comments: list[Comment]
    id_counter: int

    def __init__(self, id_generator: IdGenerator | None = None) -> None:
        if id_generator is None:
            id_generator = IdGenerator()
        self.id_generator = id_generator
        self.reset()

    def reset(self) -> None:
        self.stack = [AstNode("None")]
        self.comments = []
        self.id_counter = 0

    def start_rule(self, rule_type: str) -> None:
        self.stack.append(AstNode(rule_type))

    def end_rule(self, rule_type: str) -> None:
        node = self.stack.pop()
        self.current_node.add(node.rule_type, self.transform_node(node))

    def build(self, token: Token) -> None:
        if token.matched_type == "Comment":
            self.comments.append(
                {"location": self.get_location(token), "text": token.matched_text}
            )
        else:
            self.current_node.add(token.matched_type, token)

    def get_result(self) -> object:
        return self.current_node.get_single("GherkinDocument")

    @property
    def current_node(self) -> AstNode:
        return self.stack[-1]

    @staticmethod
    def get_location(token: Token, column: int | None = None) -> Location:
        return (
            token.location
            if not column
            else {"line": token.location["line"], "column": column}
        )

    def get_tags(self, node: AstNode) -> list[Tag]:
        tags: list[Tag] = []
        tags_node = cast(AstNode, node.get_single("Tags"))
        if not tags_node:
            return tags

        for token in tags_node.get_tokens("TagLine"):
            tags += [
                {
                    "id": self.id_generator.get_next_id(),
                    "location": self.get_location(token, tag_item["column"]),
                    "name": tag_item["text"],
                }
                for tag_item in token.matched_items
            ]

        return tags

    def get_table_rows(self, node: AstNode) -> list[TableRow]:
        rows: list[TableRow] = [
            {
                "id": self.id_generator.get_next_id(),
                "location": self.get_location(token),
                "cells": self.get_cells(token),
            }
            for token in node.get_tokens("TableRow")
        ]
        self.ensure_cell_count(rows)
        return rows

    @staticmethod
    def ensure_cell_count(rows: list[TableRow]) -> None:
        if not rows:
            return

        cell_count = len(rows[0]["cells"])
        for row in rows:
            if len(row["cells"]) != cell_count:
                raise AstBuilderException(
                    "inconsistent cell count within the table", row["location"]
                )

    def get_cells(self, table_row_token: Token) -> list[Cell]:
        return [
            cast(
                Cell,
                self.reject_nones(
                    {
                        "location": self.get_location(
                            table_row_token, cell_item["column"]
                        ),
                        "value": cell_item["text"],
                    }
                ),
            )
            for cell_item in table_row_token.matched_items
        ]

    @staticmethod
    def get_description(node: AstNode) -> str:
        return cast(str, node.get_single("Description", ""))

    @staticmethod
    def get_steps(node: AstNode) -> list[Step]:
        return cast(list[Step], node.get_items("Step"))

    def transform_node(
        self, node: AstNode
    ) -> (
        Step
        | DocString
        | DataTable
        | Background
        | Scenario
        | Examples
        | list[TableRow]
        | str
        | None
        | Rule
        | Feature
        | GherkinDocument
        | AstNode
    ):
        if node.rule_type == "Step":
            step_line = node.get_token("StepLine")
            step_argument_type = "dummy_type"
            step_argument = None
            if node.get_single("DataTable"):
                step_argument_type = "dataTable"
                step_argument = node.get_single("DataTable")
            elif node.get_single("DocString"):
                step_argument_type = "docString"
                step_argument = node.get_single("DocString")

            return self.reject_nones(
                {
                    "id": self.id_generator.get_next_id(),
                    "location": self.get_location(step_line),
                    "keyword": step_line.matched_keyword,
                    "keywordType": step_line.matched_keyword_type,
                    "text": step_line.matched_text,
                    step_argument_type: step_argument,
                }
            )
        elif node.rule_type == "DocString":
            separator_token = node.get_tokens("DocStringSeparator")[0]
            media_type = (
                separator_token.matched_text
                if len(separator_token.matched_text) > 0
                else None
            )
            line_tokens = node.get_tokens("Other")
            content = "\n".join([t.matched_text for t in line_tokens])

            return self.reject_nones(
                {
                    "location": self.get_location(separator_token),
                    "content": content,
                    "delimiter": separator_token.matched_keyword,
                    "mediaType": media_type,
                }
            )
        elif node.rule_type == "DataTable":
            rows = self.get_table_rows(node)
            return self.reject_nones(
                {
                    "location": rows[0]["location"],
                    "rows": rows,
                }
            )
        elif node.rule_type == "Background":
            background_line = node.get_token("BackgroundLine")
            description = self.get_description(node)
            steps = self.get_steps(node)

            return self.reject_nones(
                {
                    "id": self.id_generator.get_next_id(),
                    "location": self.get_location(background_line),
                    "keyword": background_line.matched_keyword,
                    "name": background_line.matched_text,
                    "description": description,
                    "steps": steps,
                }
            )
        elif node.rule_type == "ScenarioDefinition":
            tags = self.get_tags(node)
            scenario_node = cast(AstNode, node.get_single("Scenario"))
            scenario_line = scenario_node.get_token("ScenarioLine")
            description = self.get_description(scenario_node)
            steps = self.get_steps(scenario_node)
            examples = scenario_node.get_items("ExamplesDefinition")

            return self.reject_nones(
                {
                    "id": self.id_generator.get_next_id(),
                    "tags": tags,
                    "location": self.get_location(scenario_line),
                    "keyword": scenario_line.matched_keyword,
                    "name": scenario_line.matched_text,
                    "description": description,
                    "steps": steps,
                    "examples": examples,
                }
            )
        elif node.rule_type == "ExamplesDefinition":
            tags = self.get_tags(node)
            examples_node = cast(AstNode, node.get_single("Examples"))
            examples_line = examples_node.get_token("ExamplesLine")
            description = self.get_description(examples_node)
            examples_table_rows = cast(
                list[TableRow], examples_node.get_single("ExamplesTable")
            )
            table_header = examples_table_rows[0] if examples_table_rows else None
            table_body = examples_table_rows[1:] if examples_table_rows else []

            return self.reject_nones(
                {
                    "id": self.id_generator.get_next_id(),
                    "tags": tags,
                    "location": self.get_location(examples_line),
                    "keyword": examples_line.matched_keyword,
                    "name": examples_line.matched_text,
                    "description": description,
                    "tableHeader": table_header,
                    "tableBody": table_body,
                }
            )
        elif node.rule_type == "ExamplesTable":
            return self.get_table_rows(node)
        elif node.rule_type == "Description":
            line_tokens = node.get_tokens("Other")
            tokens = list(line_tokens)

            # Trim trailing empty lines
            while tokens and not tokens[-1].matched_text:
                tokens.pop()

            return "\n".join(token.matched_text for token in tokens)
        elif node.rule_type == "Rule":
            header = cast(Union[AstNode, None], node.get_single("RuleHeader"))
            if not header:
                return None
            tags = self.get_tags(header)
            rule_line = header.get_token("RuleLine")
            if not rule_line:
                return None

            children = []
            background = node.get_single("Background")
            if background:
                children.append({"background": background})
            children = children + [
                {"scenario": i} for i in node.get_items("ScenarioDefinition")
            ]
            description = self.get_description(header)

            return self.reject_nones(
                {
                    "id": self.id_generator.get_next_id(),
                    "tags": tags,
                    "location": self.get_location(rule_line),
                    "keyword": rule_line.matched_keyword,
                    "name": rule_line.matched_text,
                    "description": description,
                    "children": children,
                }
            )
        elif node.rule_type == "Feature":
            header = cast(Union[AstNode, None], node.get_single("FeatureHeader"))
            if not header:
                return None

            tags = self.get_tags(header)
            feature_line = header.get_token("FeatureLine")
            if not feature_line:
                return None

            children = []
            background = node.get_single("Background")
            if background:
                children.append({"background": background})
            children = children + [
                {"scenario": i} for i in node.get_items("ScenarioDefinition")
            ]
            children = children + [{"rule": i} for i in node.get_items("Rule")]
            description = self.get_description(header)
            language = feature_line.matched_gherkin_dialect

            return self.reject_nones(
                {
                    "tags": tags,
                    "location": self.get_location(feature_line),
                    "language": language,
                    "keyword": feature_line.matched_keyword,
                    "name": feature_line.matched_text,
                    "description": description,
                    "children": children,
                }
            )
        elif node.rule_type == "GherkinDocument":
            feature = node.get_single("Feature")

            return self.reject_nones({"feature": feature, "comments": self.comments})
        else:
            return node

    @staticmethod
    def reject_nones(values: dict[str, T | None]) -> dict[str, T]:
        return {k: v for k, v in values.items() if v is not None}
