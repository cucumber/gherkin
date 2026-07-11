/// Gherkin parser/compiler for Dart. Parses `.feature` sources into Cucumber
/// [messages](https://pub.dev/packages/cucumber_messages) envelopes.
///
/// ```dart
/// import 'package:cucumber_gherkin/cucumber_gherkin.dart';
///
/// final envelopes = generateMessages(
///   'Feature: Minimal\n\n  Scenario: A\n    Given the minimalism\n',
///   'example.feature',
/// );
/// ```
library;

export 'src/generate_messages.dart';
