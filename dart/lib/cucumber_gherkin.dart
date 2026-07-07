/// Gherkin parser/compiler for Dart. Parses `.feature` sources into Cucumber
/// [messages](https://pub.dev/packages/cucumber_messages) envelopes.
///
/// Core, platform-agnostic public library. No `dart:io` dependency, so it works
/// on the web. Import it for the whole public API:
///
/// ```dart
/// import 'package:cucumber_gherkin/cucumber_gherkin.dart';
/// ```
///
/// Exposes:
///
/// * `GherkinParser` and `IdGenerator` for parsing;
/// * `GherkinDialect`, `GherkinDialectProvider`, and `GherkinLanguageKeywords`
///   for supported languages and their localized keywords;
/// * `GherkinException` and the `ParserException` hierarchy for errors.
///
/// To read Gherkin from files, import
/// `package:cucumber_gherkin/cucumber_gherkin_io.dart` instead. It re-exports
/// everything here and adds the `dart:io` `parsePath`/`parsePaths` entry points
/// as extension methods on `GherkinParser`.
library;

export 'src/exceptions/exceptions.dart';
export 'src/gherkin/gherkin_parser.dart';
export 'src/gherkin/id_generator.dart';
export 'src/language/gherkin_dialect.dart';
export 'src/language/gherkin_dialect_provider.dart';
export 'src/language/gherkin_language_keywords.dart';
