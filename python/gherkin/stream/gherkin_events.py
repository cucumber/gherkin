from __future__ import annotations

from collections.abc import Generator, Iterable
from dataclasses import dataclass
from typing import TypedDict

from gherkin.ast_builder import AstBuilder
from gherkin.parser import Parser
from gherkin.pickles.compiler import Compiler, Pickle, GherkinDocumentWithURI
from gherkin.errors import ParserError, CompositeParserException, ParserException
from gherkin.stream.id_generator import IdGenerator
from gherkin.stream.source_events import Event
from gherkin.token import Location


class Source(TypedDict):
    uri: str
    location: Location


class ParseError(TypedDict):
    source: Source
    message: str


class Error(TypedDict):
    parseError: ParseError


def create_errors(errors: Iterable[ParserException], uri: str) -> Generator[Error]:
    for error in errors:
        yield {
            "parseError": {
                "source": {"uri": uri, "location": error.location},
                "message": str(error),
            },
        }


class GherkinDocumentEnvelope(TypedDict):
    gherkinDocument: GherkinDocumentWithURI


class PickleEnvelope(TypedDict):
    pickle: Pickle


class GherkinEvents:
    @dataclass
    class Options:
        print_source: bool
        print_ast: bool
        print_pickles: bool

    def __init__(self, options: Options) -> None:
        self.options = options
        self.id_generator = IdGenerator()
        self.parser = Parser(ast_builder=AstBuilder(self.id_generator))
        self.compiler = Compiler(self.id_generator)

    def enum(
        self, source_event: Event
    ) -> Generator[Event | Error | GherkinDocumentEnvelope | PickleEnvelope,]:
        uri = source_event["source"]["uri"]
        source = source_event["source"]["data"]

        try:
            gherkin_document = self.parser.parse(source)
            gherkin_document_with_uri: GherkinDocumentWithURI = {
                **gherkin_document,
                "uri": uri,
            }

            if self.options.print_source:
                yield source_event

            if self.options.print_ast:
                yield {"gherkinDocument": gherkin_document_with_uri}

            if self.options.print_pickles:
                pickles = self.compiler.compile(gherkin_document_with_uri)
                for pickle in pickles:
                    yield {"pickle": pickle}
        except CompositeParserException as e:
            yield from create_errors(e.errors, uri)
        except ParserError as e:
            yield from create_errors([e], uri)
