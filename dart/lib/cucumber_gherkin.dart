/// Gherkin parser/compiler for Dart. Parses `.feature` sources into Cucumber
/// [messages](https://pub.dev/packages/cucumber_messages) envelopes.
///
/// ```dart
/// import 'package:cucumber_gherkin/cucumber_gherkin.dart';
///
/// final envelopes = generateMessages(source, 'example.feature');
/// ```
library;

export 'src/gherkin/generate_messages.dart';
