from __future__ import annotations

import typing

if typing.TYPE_CHECKING:
    from gherkin.token import Location, Token


class ParserError(Exception):
    pass


class ParserException(ParserError):
    def __init__(self, message: str, location: Location) -> None:
        self.location = location
        super().__init__(f"({location['line']}:{location.get('column', 0)}): {message}")


class NoSuchLanguageException(ParserException):
    def __init__(self, language: str, location: Location) -> None:
        super().__init__(f"Language not supported: {language}", location)


class AstBuilderException(ParserException):
    pass


class UnexpectedEOFException(ParserException):
    def __init__(
        self,
        received_token: Token,
        expected_token_types: list[str],
        state_comment: str,
    ) -> None:
        message = f"unexpected end of file, expected: {', '.join(expected_token_types)}"
        super().__init__(message, received_token.location)


class UnexpectedTokenException(ParserException):
    def __init__(
        self,
        received_token: Token,
        expected_token_types: list[str],
        state_comment: str,
    ) -> None:
        message = f"expected: {', '.join(expected_token_types)}, got '{received_token.token_value().strip()}'"
        column = received_token.location.get("column", None)
        location = (
            received_token.location
            if column
            else {
                "line": received_token.location["line"],
                "column": received_token.line.indent + 1,
            }
        )
        super().__init__(message, location)


class CompositeParserException(ParserError):
    def __init__(self, errors: list[ParserException]) -> None:
        self.errors = errors
        super().__init__(
            "Parser errors:\n" + "\n".join([error.args[0] for error in errors]),
        )
