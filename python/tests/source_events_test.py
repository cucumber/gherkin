from pathlib import Path

from gherkin.stream.source_events import source_event


def test_should_resolve_classic_feature():
    actual = source_event(Path(__file__).parents[2] / "testdata/good/minimal.feature")
    assert actual["source"]["mediaType"] == "text/x.cucumber.gherkin+plain"


def test_should_resolve_markdown_feature():
    actual = source_event(
        Path(__file__).parents[2] / "testdata/good/minimal.feature.md",
    )
    assert actual["source"]["mediaType"] == "text/x.cucumber.gherkin+markdown"
