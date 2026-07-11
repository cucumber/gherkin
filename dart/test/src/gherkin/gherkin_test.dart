import 'package:cucumber_gherkin/cucumber_gherkin.dart';
import 'package:test/test.dart';

void main() {
  const source =
      'Feature: Minimal\n'
      '\n'
      '  Scenario: minimalistic\n'
      '    Given the minimalism\n';

  test('parses source into message envelopes', () async {
    final envelopes =
        await GherkinParser().parseString(source, 'minimal.feature').toList();

    expect(envelopes, hasLength(3));
    expect(envelopes.first.source!.uri, 'minimal.feature');
    final gherkinDocument = envelopes[1].gherkinDocument!;
    final feature = gherkinDocument.feature!;
    expect('Minimal', feature.name);
    expect(envelopes.last.pickle!.name, 'minimalistic');
  });

  test('reports malformed input as a parseError envelope', () async {
    final envelopes =
        await GherkinParser()
            .parseString('not gherkin', 'bad.feature')
            .toList();

    final error = envelopes.last.parseError!;
    expect(error.message, startsWith('(1:1): '));
    expect(error.source.location!.line, 1);
  });
}
