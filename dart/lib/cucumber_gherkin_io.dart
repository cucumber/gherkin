/// File-system entry points for the Gherkin parser.
///
/// Re-exports the platform-agnostic
/// `package:cucumber_gherkin/cucumber_gherkin.dart` API and adds the `dart:io`
/// file-reading entry points as extension methods on `GherkinParser`:
///
/// ```dart
/// import 'package:cucumber_gherkin/cucumber_gherkin_io.dart';
///
/// final parser = GherkinParser();
/// final envelopes = await parser.parsePath('example/minimal.feature').toList();
/// ```
///
/// Import this library on platforms with a file system (Dart VM, Flutter
/// mobile/desktop, server-side). On the web, import the core
/// `package:cucumber_gherkin/cucumber_gherkin.dart` library and feed Gherkin
/// via `parseString`/`parseEnvelope`/`parseEnvelopes`.
library;

export 'cucumber_gherkin.dart';
export 'src/gherkin/gherkin_parser_io.dart' show GherkinParserIo;
