import 'package:cucumber_gherkin/cucumber_gherkin.dart';
import 'package:test/test.dart';

void main() {
  const source =
      'Feature: Minimal\n'
      '\n'
      '  Scenario: minimalistic\n'
      '    Given the minimalism\n';

  test('parses source into message envelopes', () {
    final envelopes = generateMessages(source, 'minimal.feature');

    expect(envelopes, hasLength(3));
    expect(envelopes.first.source!.uri, 'minimal.feature');
    final gherkinDocument = envelopes[1].gherkinDocument!;
    final feature = gherkinDocument.feature!;
    expect(feature.name, 'Minimal');
    expect(envelopes.last.pickle!.name, 'minimalistic');
  });

  test('honors include flags', () {
    final envelopes = generateMessages(
      source,
      'minimal.feature',
      const GherkinOptions(
        includeSource: false,
        includePickles: false,
      ),
    );

    expect(envelopes, hasLength(1));
    expect(envelopes.single.gherkinDocument, isNotNull);
  });

  test('uses a custom id generator', () {
    var nextId = 0;
    final envelopes = generateMessages(
      source,
      'minimal.feature',
      GherkinOptions(includeSource: false, idGenerator: () => 'id-${nextId++}'),
    );

    final scenario =
        envelopes.first.gherkinDocument!.feature!.children.first.scenario!;
    expect(scenario.steps.first.id, 'id-0');
    expect(scenario.id, 'id-1');
    expect(envelopes.last.pickle!.id, startsWith('id-'));
  });

  test('reports parse errors as envelopes', () {
    final envelopes = generateMessages(
      'not gherkin\n',
      'broken.feature',
      const GherkinOptions(includeSource: false, includePickles: false),
    );

    expect(envelopes, hasLength(1));
    expect(envelopes.single.parseError, isNotNull);
    expect(envelopes.single.parseError!.source.uri, 'broken.feature');
  });
}
