/// File-system-enabled entry points for the Gherkin parser.
///
/// This library re-exports the entire platform-agnostic
/// `package:cucumber_gherkin/cucumber_gherkin.dart` API and additionally
/// provides the `dart:io`-based file-reading entry points as extension methods
/// on [GherkinParser]:
///
/// ```dart
/// import 'package:cucumber_gherkin/cucumber_gherkin_io.dart';
///
/// final parser = GherkinParser();
/// final envelopes = await parser.parsePath('example/minimal.feature').toList();
/// ```
///
/// Import this library on platforms that have a file system (the Dart VM,
/// Flutter mobile/desktop, server-side). On the web, import the core
/// `package:cucumber_gherkin/cucumber_gherkin.dart` library instead and feed
/// Gherkin in via `parseString`/`parseEnvelope`/`parseEnvelopes`.
library;

export 'cucumber_gherkin.dart';
export 'src/gherkin/gherkin_parser_io.dart' show GherkinParserIo;
