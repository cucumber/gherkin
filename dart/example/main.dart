import 'package:cucumber_gherkin/cucumber_gherkin.dart';

void main() {
  final envelopes = generateMessages(
    'Feature: Minimal\n\n  Scenario: minimalistic\n    Given the minimalism\n',
    'minimal.feature',
  );

  print('Generated ${envelopes.length} message envelopes.');
}
