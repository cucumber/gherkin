from gherkin.stream.source_events import source_event

from os import path


def test_should_resolve_classic_feature():
    actual = source_event(
        path.join(
            path.dirname(__file__), "..", "..", "testdata", "good", "minimal.feature"
        )
    )
    assert actual["source"]["mediaType"] == "text/x.cucumber.gherkin+plain"


def test_should_resolve_markdown_feature():
    actual = source_event(
        path.join(
            path.dirname(__file__), "..", "..", "testdata", "good", "minimal.feature.md"
        )
    )
    assert actual["source"]["mediaType"] == "text/x.cucumber.gherkin+markdown"
