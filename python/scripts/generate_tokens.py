import sys

from gherkin.parser import Parser
from gherkin.token_formatter_builder import TokenFormatterBuilder
from gherkin.token_matcher_markdown import GherkinInMarkdownTokenMatcher
from gherkin.token_scanner import TokenScanner


def main() -> None:
    files = sys.argv[1:]
    parser = Parser(TokenFormatterBuilder())
    for file in files:
        source = open(file, encoding="utf8", newline="").read()  # noqa: PTH123
        scanner = TokenScanner(source)

        if file.endswith(".md"):
            print(parser.parse(scanner, GherkinInMarkdownTokenMatcher()))
        else:
            print(parser.parse(scanner))


if __name__ == "__main__":
    main()
