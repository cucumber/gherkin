import 'package:cucumber_gherkin/cucumber_gherkin.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  var nextId = 0;
  String nextIdGenerator() => (nextId++).toString();
  const source =
      'Feature: Minimal\n'
      '\n'
      '  Scenario: minimalistic\n'
      '    Given the minimalism\n';

  test('parses source into pickles', () async {
    final envelopeStream = GherkinParser(
      includeSource: false,
      idGenerator: nextIdGenerator,
    ).parseString(source, 'minimal.feature');

    final pickleStream = envelopeStream.where(
      (envelope) => envelope.pickle != null,
    );

    final envelope = await pickleStream.first;
    expect('minimalistic', envelope.pickle!.name);
  });

  test('emits the Gherkin document', () async {
    final envelopes =
        await GherkinParser(
          includeSource: false,
          includePickles: false,
          idGenerator: nextIdGenerator,
        ).parseString(source, 'minimal.feature').toList();

    final gherkinDocument = envelopes.first.gherkinDocument!;
    final feature = gherkinDocument.feature!;
    expect('Minimal', feature.name);

    final scenario = feature.children.first.scenario!;
    expect('minimalistic', scenario.name);
  });

  test('parses source envelopes', () async {
    final envelope = GherkinParser.makeSourceEnvelope(
      'Feature: Minimal\n'
          '\n'
          '  Scenario: minimalistic\n'
          '    Given the minimalism\n',
      'test.feature',
    );

    final singletonList = <messages.Envelope>[envelope];

    final envelopes =
        await GherkinParser(
          includeSource: false,
          includePickles: false,
          idGenerator: nextIdGenerator,
        ).parseEnvelopes(Stream.fromIterable(singletonList)).toList();

    final gherkinDocument = envelopes.first.gherkinDocument!;
    final feature = gherkinDocument.feature!;
    expect('Minimal', feature.name);
  });

  group('makeSourceEnvelope media-type inference', () {
    test('infers the plain media type from a .feature uri', () {
      final envelope = GherkinParser.makeSourceEnvelope('', 'a.feature');
      expect(
        envelope.source!.mediaType,
        messages.SourceMediaType.textXCucumberGherkinPlain,
      );
    });

    test('throws ArgumentError for an unrecognized extension with no '
        'mediaType', () {
      expect(
        () => GherkinParser.makeSourceEnvelope('', 'a.txt'),
        throwsA(isA<ArgumentError>()),
      );
    });

    test('uses an explicit mediaType when the uri has no recognized '
        'extension', () {
      final envelope = GherkinParser.makeSourceEnvelope(
        '',
        'a.txt',
        mediaType: messages.SourceMediaType.textXCucumberGherkinPlain,
      );
      expect(
        envelope.source!.mediaType,
        messages.SourceMediaType.textXCucumberGherkinPlain,
      );
    });

    test('an explicit mediaType overrides the uri extension', () {
      final envelope = GherkinParser.makeSourceEnvelope(
        '',
        'a.feature',
        mediaType: messages.SourceMediaType.textXCucumberGherkinPlain,
      );
      expect(
        envelope.source!.mediaType,
        messages.SourceMediaType.textXCucumberGherkinPlain,
      );
    });
  });
}
