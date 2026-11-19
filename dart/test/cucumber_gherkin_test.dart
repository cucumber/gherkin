import 'package:cucumber_gherkin/cucumber_gherkin.dart';
import 'package:test/test.dart';

void main() {
  const source =
      'Feature: Minimal\n'
      '\n'
      '  Scenario: minimalistic\n'
      '    Given the minimalism\n';

  test('includes source, document and pickle envelopes by default', () {
    final envelopes = generateMessages(source, 'minimal.feature');

    expect(envelopes, hasLength(3));
    expect(envelopes.first.source!.uri, 'minimal.feature');
    expect(envelopes[1].gherkinDocument, isNotNull);
    expect(envelopes.last.pickle, isNotNull);
  });

  test('can emit only the document', () {
    final envelopes = generateMessages(
      source,
      'minimal.feature',
      const GherkinOptions(includeSource: false, includePickles: false),
    );

    expect(envelopes, hasLength(1));
    expect(envelopes.single.gherkinDocument, isNotNull);
  });

  test('source-only mode does not parse invalid input or generate IDs', () {
    final envelopes = generateMessages(
      'invalid input',
      'invalid.feature',
      GherkinOptions(
        includeGherkinDocument: false,
        includePickles: false,
        idGenerator: () => throw StateError('unexpected ID request'),
      ),
    );
    expect(envelopes, hasLength(1));
    expect(envelopes.single.source!.data, 'invalid input');
  });

  test('can emit pickles without emitting the document or source', () {
    final envelopes = generateMessages(
      source,
      'minimal.feature',
      const GherkinOptions(
        includeSource: false,
        includeGherkinDocument: false,
      ),
    );
    expect(envelopes, hasLength(1));
    expect(envelopes.single.pickle, isNotNull);
  });

  test('returns no envelopes when all output is disabled', () {
    expect(
      generateMessages(
        'invalid input',
        'invalid.feature',
        GherkinOptions(
          includeSource: false,
          includeGherkinDocument: false,
          includePickles: false,
          idGenerator: () => throw StateError('unexpected ID request'),
        ),
      ),
      isEmpty,
    );
  });

  test('uses caller-generated IDs for AST and pickle elements', () {
    final generatedIds = <String>[];
    String generateId() {
      final id = 'custom-${generatedIds.length}';
      generatedIds.add(id);
      return id;
    }

    final envelopes = generateMessages(
      source,
      'minimal.feature',
      GherkinOptions(includeSource: false, idGenerator: generateId),
    );

    final scenario =
        envelopes.first.gherkinDocument!.feature!.children.first.scenario!;
    final pickle = envelopes.last.pickle!;
    expect(
      [
        scenario.id,
        scenario.steps.single.id,
        pickle.id,
        pickle.steps.single.id,
      ],
      unorderedEquals(generatedIds),
    );
  });

  test('propagates failures from the caller-provided ID generator', () {
    final failure = StateError('ID allocation failed');

    expect(
      () => generateMessages(
        source,
        'minimal.feature',
        GherkinOptions(idGenerator: () => throw failure),
      ),
      throwsA(same(failure)),
    );
  });

  test('retains the source on failure without emitting successful results', () {
    final envelopes = generateMessages(
      'not gherkin\n',
      'broken.feature',
    );

    expect(envelopes.length, greaterThan(1));
    expect(envelopes.first.source!.data, 'not gherkin\n');
    expect(
      envelopes.skip(1).map((envelope) => envelope.parseError?.source.uri),
      everyElement('broken.feature'),
    );
    expect(
      envelopes.map((envelope) => envelope.gherkinDocument),
      everyElement(isNull),
    );
    expect(envelopes.map((envelope) => envelope.pickle), everyElement(isNull));
  });
}
