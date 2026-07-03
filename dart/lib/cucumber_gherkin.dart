/// Gherkin parser/compiler for Dart: parses `.feature` and Markdown sources
/// into Cucumber [messages](https://pub.dev/packages/cucumber_messages)
/// envelopes.
///
/// This is the package's core, platform-agnostic public library (it does not
/// depend on `dart:io`, so it works on the web). Import it to access the whole
/// public API:
///
/// ```dart
/// import 'package:cucumber_gherkin/cucumber_gherkin.dart';
/// ```
///
/// It exposes:
///
/// * [GherkinParser] and [IdGenerator] for parsing;
/// * [GherkinDialect] and [GherkinDialectProvider] for the supported languages
///   and their localized keywords;
/// * [GherkinException] and the [ParserException] hierarchy for errors.
///
/// To read Gherkin directly from files, import
/// `package:cucumber_gherkin/cucumber_gherkin_io.dart` instead: it re-exports
/// everything here and adds the `dart:io`-based `parsePath`/`parsePaths` entry
/// points as extension methods on [GherkinParser].
library;

export 'src/exceptions/exceptions.dart';
export 'src/gherkin/gherkin_parser.dart';
export 'src/gherkin/id_generator.dart';
export 'src/language/gherkin_dialect.dart';
export 'src/language/gherkin_dialect_provider.dart';
export 'src/language/gherkin_language_keywords.dart';
