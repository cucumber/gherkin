import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/generate_messages.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
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
      const GherkinOptions(includeSource: false, includePickles: false),
    );

    expect(envelopes, hasLength(1));
    expect(envelopes.single.gherkinDocument, isNotNull);
  });

  test('can omit every envelope type without parsing', () {
    expect(
      generateMessages(
        'not gherkin',
        'ignored.feature',
        const GherkinOptions(
          includeSource: false,
          includeGherkinDocument: false,
          includePickles: false,
        ),
      ),
      isEmpty,
    );
  });

  test('uses a custom ID generator', () {
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

  test('uses UUID v4 IDs by default', () {
    final document = generateMessages(
      'Feature: IDs\n  Scenario: generated\n    Given an ID\n',
      'ids.feature',
      const GherkinOptions(includeSource: false),
    ).first.gherkinDocument!;

    expect(
      document.feature!.children.single.scenario!.id,
      matches(
        RegExp(
          r'^[0-9a-f]{8}-[0-9a-f]{4}-4[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$',
        ),
      ),
    );
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

  test('reports a parser error raised by the parser seam', () {
    final envelopes = generateMessagesWithParser(
      'source',
      'broken.feature',
      (_, _) => throw ParserException.create(
        'broken',
        const messages.Location(line: 3, column: 2),
      ),
      const GherkinOptions(includeSource: false),
    );

    expect(envelopes.single.parseError!.message, '(3:2): broken');
  });
}
