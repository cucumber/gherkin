from __future__ import annotations

import re
from collections.abc import Iterable, Sequence
from typing import TypedDict, Any, cast, overload
from typing_extensions import TypeIs, NotRequired

from ..parser_types import (
    GherkinDocument,
    Envelope,
    BackgroundEnvelope,
    RuleEnvelope,
    Scenario,
    ScenarioEnvelope,
    Tag,
    Rule,
    Step,
    Cell,
)
from ..stream.id_generator import IdGenerator


class GherkinDocumentWithURI(GherkinDocument):
    uri: str


class PickleTag(TypedDict):
    astNodeId: str
    name: str


class PickleArgumentEnvelope(TypedDict):
    pass


class PickleArgumentDataTableCell(TypedDict):
    value: str


class PickleArgumentDataTableRow(TypedDict):
    cells: list[PickleArgumentDataTableCell]


class PickleArgumentDataTable(TypedDict):
    rows: list[PickleArgumentDataTableRow]


class PickleArgumentDataTableEnvelope(PickleArgumentEnvelope):
    dataTable: PickleArgumentDataTable


class PickleArgumentDocString(TypedDict):
    content: str | None
    mediaType: NotRequired[str | None]


class PickleArgumentDocStringEnvelope(PickleArgumentEnvelope):
    docString: PickleArgumentDocString


class PickleStep(TypedDict):
    astNodeIds: list[str]
    id: str
    type: str
    text: str
    argument: NotRequired[PickleArgumentEnvelope]


class Pickle(TypedDict):
    astNodeIds: list[str]
    id: str
    tags: list[PickleTag]
    name: str
    language: str
    steps: list[PickleStep]
    uri: str


def is_background_container(container: Envelope) -> TypeIs[BackgroundEnvelope]:
    return "background" in container


def is_rule_container(container: Envelope) -> TypeIs[RuleEnvelope]:
    return "rule" in container


def is_scenario_container(container: Envelope) -> TypeIs[ScenarioEnvelope]:
    return "scenario" in container


class Compiler:
    id_generator: IdGenerator

    def __init__(self, id_generator: IdGenerator | None = None) -> None:
        if id_generator is None:
            id_generator = IdGenerator()
        self.id_generator = id_generator

    def compile(self, gherkin_document: GherkinDocumentWithURI) -> list[Pickle]:
        pickles: list[Pickle] = []
        if "feature" not in gherkin_document:
            return pickles

        feature = gherkin_document["feature"]
        if not feature["children"]:
            return pickles

        uri = gherkin_document["uri"]
        feature_tags = feature["tags"]
        language = feature["language"]
        background_steps: list[Step] = []
        for scenario_definition in feature["children"]:
            if is_background_container(scenario_definition):
                if scenario_definition["background"]["steps"]:
                    background_steps += scenario_definition["background"]["steps"]
            elif is_rule_container(scenario_definition):
                self._compile_rule(
                    uri,
                    feature_tags,
                    background_steps,
                    scenario_definition["rule"],
                    language,
                    pickles,
                )
            else:
                assert is_scenario_container(scenario_definition)
                scenario = scenario_definition["scenario"]
                args = (
                    uri,
                    feature_tags,
                    background_steps,
                    scenario,
                    language,
                    pickles,
                )
                if not scenario["examples"]:
                    self._compile_scenario(*args)
                else:
                    self._compile_scenario_outline(*args)
        return pickles

    def _compile_rule(
        self,
        uri: str,
        feature_tags: list[Tag],
        feature_background_steps: list[Step],
        rule: Rule,
        language: str,
        pickles: list[Pickle],
    ) -> list[Pickle]:
        tags = list(feature_tags) + list(rule["tags"])
        background_steps = []
        background_steps += feature_background_steps
        for scenario_definition in rule["children"]:
            if is_background_container(scenario_definition):
                if scenario_definition["background"]["steps"]:
                    background_steps += scenario_definition["background"]["steps"]
            else:
                assert is_scenario_container(scenario_definition)
                scenario = scenario_definition["scenario"]
                args = (uri, tags, background_steps, scenario, language, pickles)
                if not scenario["examples"]:
                    self._compile_scenario(*args)
                else:
                    self._compile_scenario_outline(*args)
        return pickles

    def _compile_scenario(
        self,
        uri: str,
        inherited_tags: list[Tag],
        background_steps: list[Any],
        scenario: Scenario,
        language: str,
        pickles: list[Pickle],
    ) -> None:
        tags = list(inherited_tags) + list(scenario["tags"])
        last_keyword_type = "Unknown"
        steps = list()
        if scenario["steps"]:
            for step in background_steps + scenario["steps"]:
                last_keyword_type = (
                    last_keyword_type
                    if step["keywordType"] == "Conjunction"
                    else step["keywordType"]
                )
                steps.append(self._pickle_step(step, last_keyword_type))

        pickle: Pickle = {
            "astNodeIds": [scenario["id"]],
            "id": self.id_generator.get_next_id(),
            "tags": self._pickle_tags(tags),
            "name": cast(str, scenario["name"]),
            "language": language,
            "steps": steps,
            "uri": uri,
        }
        pickles.append(pickle)

    def _compile_scenario_outline(
        self,
        uri: str,
        inherited_tags: list[Tag],
        background_steps: list[Step],
        scenario: Scenario,
        language: str,
        pickles: list[Pickle],
    ) -> None:
        for examples in scenario["examples"]:
            if "tableHeader" not in examples:
                continue

            variable_cells = examples["tableHeader"]["cells"]

            for values in examples["tableBody"]:
                value_cells = values["cells"]
                tags = (
                    list(inherited_tags)
                    + list(scenario["tags"])
                    + list(examples["tags"])
                )
                last_keyword_type = None
                steps = list()
                if scenario["steps"]:
                    for step in background_steps:
                        last_keyword_type = (
                            last_keyword_type
                            if step["keywordType"] == "Conjunction"
                            else step["keywordType"]
                        )
                        steps.append(self._pickle_step(step, last_keyword_type))

                if scenario["steps"]:
                    for outline_step in scenario["steps"]:
                        last_keyword_type = (
                            last_keyword_type
                            if outline_step["keywordType"] == "Conjunction"
                            else outline_step["keywordType"]
                        )
                        step_text = self._interpolate(
                            outline_step["text"], variable_cells, value_cells
                        )
                        argument = self._create_pickle_arguments(
                            outline_step, variable_cells, value_cells
                        )
                        _pickle_step: PickleStep = {
                            "astNodeIds": [outline_step["id"], values["id"]],
                            "id": self.id_generator.get_next_id(),
                            "type": last_keyword_type,
                            "text": step_text,
                        }
                        if argument is not None:
                            _pickle_step["argument"] = argument

                        steps.append(_pickle_step)

                pickle: Pickle = {
                    "astNodeIds": [scenario["id"], values["id"]],
                    "id": self.id_generator.get_next_id(),
                    "name": self._interpolate(
                        scenario["name"], variable_cells, value_cells
                    ),
                    "language": language,
                    "steps": steps,
                    "tags": self._pickle_tags(tags),
                    "uri": uri,
                }
                pickles.append(pickle)

    def _create_pickle_arguments(
        self,
        step: Step,
        variables: Sequence[Cell],
        values: Sequence[Cell],
    ) -> PickleArgumentEnvelope | None:
        if "dataTable" in step:
            table: PickleArgumentDataTable = {"rows": []}
            for row in step["dataTable"]["rows"]:
                cells: list[PickleArgumentDataTableCell] = [
                    {"value": self._interpolate(cell["value"], variables, values)}
                    for cell in row["cells"]
                ]
                table["rows"].append({"cells": cells})
            return PickleArgumentDataTableEnvelope(dataTable=table)
        elif "docString" in step:
            argument = step["docString"]
            docstring: PickleArgumentDocString = {
                "content": self._interpolate(argument["content"], variables, values)
            }
            if "mediaType" in argument:
                docstring["mediaType"] = self._interpolate(
                    argument["mediaType"], variables, values
                )
            return PickleArgumentDocStringEnvelope(docString=docstring)
        else:
            return None

    @overload
    def _interpolate(
        self,
        name: str,
        variable_cells: Iterable[Cell],
        value_cells: Sequence[Cell],
    ) -> str: ...

    @overload
    def _interpolate(
        self,
        name: None,
        variable_cells: Iterable[Cell],
        value_cells: Sequence[Cell],
    ) -> None: ...

    def _interpolate(
        self,
        name: str | None,
        variable_cells: Iterable[Cell],
        value_cells: Sequence[Cell],
    ) -> str | None:
        if name is None:
            return name

        for n, variable_cell in enumerate(variable_cells):
            value_cell = value_cells[n]
            # For the case of trailing backslash, re-escaping backslashes are needed
            reescaped_value = re.sub(r"\\", r"\\\\", value_cell["value"])
            name = re.sub("<{0[value]}>".format(variable_cell), reescaped_value, name)
        return name

    def _pickle_step(self, step: Step, keyword_type: str) -> PickleStep:
        pickle_step: PickleStep = {
            "astNodeIds": [step["id"]],
            "id": self.id_generator.get_next_id(),
            "type": keyword_type,
            "text": step["text"],
        }
        argument = self._create_pickle_arguments(step, [], [])
        if argument is not None:
            pickle_step["argument"] = argument
        return pickle_step

    def _pickle_tags(self, tags: Iterable[Tag]) -> list[PickleTag]:
        return [self._pickle_tag(tag) for tag in tags]

    @staticmethod
    def _pickle_tag(tag: Tag) -> PickleTag:
        return {"astNodeId": tag["id"], "name": tag["name"]}
