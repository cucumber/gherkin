import sys

from gherkin.token_scanner import TokenScanner
from gherkin.token_formatter_builder import TokenFormatterBuilder
from gherkin.parser import Parser


def main() -> None:
    files = sys.argv[1:]
    parser = Parser(TokenFormatterBuilder())
    for file in files:
        scanner = TokenScanner(file)
        print(parser.parse(scanner))


if __name__ == "__main__":
    main()
