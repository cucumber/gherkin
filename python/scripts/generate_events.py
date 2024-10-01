from optparse import OptionParser
import json

from gherkin.stream.gherkin_events import GherkinEvents
from gherkin.stream.source_events import SourceEvents


def create_arg_parser() -> OptionParser:
    parser = OptionParser()
    parser.add_option(
        "--no-source",
        action="store_false",
        dest="print_source",
        default=True,
        help="don't print source events",
    )
    parser.add_option(
        "--no-ast",
        action="store_false",
        dest="print_ast",
        default=True,
        help="don't print ast events",
    )
    parser.add_option(
        "--no-pickles",
        action="store_false",
        dest="print_pickles",
        default=True,
        help="don't print pickle events",
    )
    return parser


def main() -> None:
    arg_parser = create_arg_parser()

    options, args = arg_parser.parse_args()

    source_events = SourceEvents(args)
    gherkin_events = GherkinEvents(
        GherkinEvents.Options(
            print_source=options.print_source,
            print_ast=options.print_ast,
            print_pickles=options.print_pickles,
        )
    )

    for source_event in source_events.enum():
        for event in gherkin_events.enum(source_event):
            print(json.dumps(event))


if __name__ == "__main__":
    main()
