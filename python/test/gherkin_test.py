import pytest

from gherkin.errors import CompositeParserException, ParserError
from gherkin.parser import Parser
from gherkin.token_matcher import TokenMatcher
from gherkin.token_matcher_markdown import GherkinInMarkdownTokenMatcher
from gherkin.token_scanner import TokenScanner


def test_parser():
    parser = Parser()
    feature_file = parser.parse(TokenScanner("Feature: Foo"))
    expected = {
        "comments": [],
        "feature": {
            "keyword": "Feature",
            "language": "en",
            "location": {"column": 1, "line": 1},
            "name": "Foo",
            "description": "",
            "children": [],
            "tags": [],
        },
    }

    assert expected == feature_file


def test_parse_multiple_features():
    parser = Parser()
    ff1 = parser.parse(TokenScanner("Feature: 1"))
    ff2 = parser.parse(TokenScanner("Feature: 2"))

    assert ff1["feature"]["name"] == "1"
    assert ff2["feature"]["name"] == "2"


def test_parse_feature_after_parser_error():
    parser = Parser()
    with pytest.raises(ParserError):
        parser.parse(
            TokenScanner(
                "# a comment\n"
                "Feature: Foo\n"
                "  Scenario: Bar\n"
                "    Given x\n"
                "      ```\n"
                "      unclosed docstring\n",
            ),
        )
    feature_file = parser.parse(
        TokenScanner(
            "Feature: Foo\n" + "  Scenario: Bar\n" + "    Given x\n"
            '      """\n'
            "      closed docstring\n"
            '      """\n',
        ),
    )
    expected = [
        {
            "scenario": {
                "id": "1",
                "name": "Bar",
                "description": "",
                "keyword": "Scenario",
                "tags": [],
                "steps": [
                    {
                        "id": "0",
                        "text": "x",
                        "location": {"column": 5, "line": 3},
                        "keyword": "Given ",
                        "keywordType": "Context",
                        "docString": {
                            "content": "closed docstring",
                            "delimiter": '"""',
                            "location": {"column": 7, "line": 4},
                        },
                    },
                ],
                "location": {"column": 3, "line": 2},
                "examples": [],
            },
        },
    ]

    assert expected == feature_file["feature"]["children"]


def test_change_the_default_language():
    parser = Parser()
    matcher = TokenMatcher("no")
    feature_file = parser.parse(TokenScanner("Egenskap: i18n support - åæø"), matcher)
    expected = {
        "comments": [],
        "feature": {
            "keyword": "Egenskap",
            "language": "no",
            "location": {"column": 1, "line": 1},
            "name": "i18n support - åæø",
            "description": "",
            "children": [],
            "tags": [],
        },
    }

    assert expected == feature_file


def test_parsing_markdown_does_not_parse_a_feature_description():
    parser = Parser()
    matcher = GherkinInMarkdownTokenMatcher()

    feature_file = """# Feature: hello
This is the
description
"""
    ast = parser.parse(TokenScanner(feature_file), matcher)
    expected = {
        "feature": {
            "tags": [],
            "description": "",
            "location": {"line": 1, "column": 3},
            "language": "en",
            "keyword": "Feature",
            "name": "hello",
            "children": [],
        },
        "comments": [],
    }
    assert ast == expected


def test_parsing_markdown_parses_a_feature_without_a_hash_Feature_header():
    parser = Parser()
    matcher = GherkinInMarkdownTokenMatcher()
    feature_file = """# Hello
This is the
description

## Scenario: hello
+ Given a step

## Some other header
"""
    ast = parser.parse(TokenScanner(feature_file), matcher)
    expected = {
        "feature": {
            "tags": [],
            "location": {
                "line": 1,
                "column": 1,
            },
            "language": "en",
            "name": "# Hello",
            "description": "",
            "children": [
                {
                    "scenario": {
                        "id": "1",
                        "tags": [],
                        "location": {
                            "line": 5,
                            "column": 4,
                        },
                        "keyword": "Scenario",
                        "name": "hello",
                        "description": "",
                        "steps": [
                            {
                                "id": "0",
                                "location": {
                                    "line": 6,
                                    "column": 3,
                                },
                                "keyword": "Given ",
                                "keywordType": "Context",
                                "text": "a step",
                            },
                        ],
                        "examples": [],
                    },
                },
            ],
        },
        "comments": [],
    }
    assert ast == expected


def test_it_parses_markdown_data_tables_with_headers():
    parser = Parser()
    matcher = GherkinInMarkdownTokenMatcher()
    markdown = """## Feature: DataTables

### Scenario: minimalistic

* Given a simple data table 
  | foo | bar |
  | --- | --- |
  | boz | boo |
"""
    ast = parser.parse(TokenScanner(markdown), matcher)
    expected = {
        "comments": [],
        "feature": {
            "children": [
                {
                    "scenario": {
                        "description": "",
                        "examples": [],
                        "id": "3",
                        "keyword": "Scenario",
                        "location": {"column": 5, "line": 3},
                        "name": "minimalistic",
                        "steps": [
                            {
                                "dataTable": {
                                    "location": {"column": 3, "line": 6},
                                    "rows": [
                                        {
                                            "cells": [
                                                {
                                                    "location": {
                                                        "column": 5,
                                                        "line": 6,
                                                    },
                                                    "value": "foo",
                                                },
                                                {
                                                    "location": {
                                                        "column": 11,
                                                        "line": 6,
                                                    },
                                                    "value": "bar",
                                                },
                                            ],
                                            "id": "0",
                                            "location": {"column": 3, "line": 6},
                                        },
                                        {
                                            "cells": [
                                                {
                                                    "location": {
                                                        "column": 5,
                                                        "line": 8,
                                                    },
                                                    "value": "boz",
                                                },
                                                {
                                                    "location": {
                                                        "column": 11,
                                                        "line": 8,
                                                    },
                                                    "value": "boo",
                                                },
                                            ],
                                            "id": "1",
                                            "location": {"column": 3, "line": 8},
                                        },
                                    ],
                                },
                                "id": "2",
                                "keyword": "Given ",
                                "keywordType": "Context",
                                "location": {"column": 3, "line": 5},
                                "text": "a simple data table",
                            },
                        ],
                        "tags": [],
                    },
                },
            ],
            "description": "",
            "keyword": "Feature",
            "language": "en",
            "location": {"column": 4, "line": 1},
            "name": "DataTables",
            "tags": [],
        },
    }
    assert ast == expected


@pytest.mark.parametrize("trailing_text", ["\\", "\\ "])
def test_inconsistent_cell_count_with_trailing_escape(trailing_text):
    feature_text = (
        """Feature:
    Scenario:
      Given I have a table
        | Name | Value |
        | A    | """
        + trailing_text
    )
    parser = Parser()

    with pytest.raises(
        CompositeParserException,
        match="inconsistent cell count within the table",
    ):
        parser.parse(TokenScanner(feature_text))
