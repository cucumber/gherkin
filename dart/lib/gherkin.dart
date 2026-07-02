/// Gherkin parser/compiler: parses `.feature` and Markdown sources into
/// Cucumber [messages](https://pub.dev/packages/cucumber_messages) envelopes.
///
/// The main entry points are [GherkinParser] and the static [Gherkin] helpers.
library;

export 'src/gherkin/gherkin_parser.dart';
export 'src/gherkin/id_generator.dart';
