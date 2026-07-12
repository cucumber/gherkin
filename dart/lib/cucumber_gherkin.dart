/// Gherkin parser/compiler for Dart. Parses `.feature` sources into
/// [Cucumber Messages](https://pub.dev/packages/cucumber_messages) envelopes.
///
/// ```dart
/// import 'package:cucumber_gherkin/cucumber_gherkin.dart';
///
/// final envelopes = generateMessages(
///   'Feature: Minimal\n\n  Scenario: minimalistic\n    Given the minimalism\n',
///   'minimal.feature',
/// );
/// ```
library;

export 'src/generate_messages.dart';
