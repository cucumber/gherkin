/// Gherkin parser/compiler for Dart. Parses `.feature` sources into
/// [Cucumber Messages](https://github.com/cucumber/messages) envelopes (via
/// [`cucumber_messages`](https://pub.dev/packages/cucumber_messages)).
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
