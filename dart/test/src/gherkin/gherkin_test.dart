import 'package:cucumber_gherkin/cucumber_gherkin_io.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  final idGenerator = IdGenerator.incrementingGenerator;

  test('Use this in readme', () async {
    const paths = <String>['../testdata/good/minimal.feature'];
    const includeSource = false;
    final envelopeStream = GherkinParser(
      includeSource: includeSource,
      idGenerator: idGenerator,
    ).parsePaths(paths);

    final pickleStream = envelopeStream.where(
      (envelope) => envelope.pickle != null,
    );

    final envelope = await pickleStream.first;
    expect('minimalistic', envelope.pickle!.name);
  });

  test('Provides access to the ast', () async {
    const paths = <String>['../testdata/good/minimal.feature'];
    const includeSource = false;
    const includePickles = false;
    final envelopes =
        await GherkinParser(
          includeSource: includeSource,
          includePickles: includePickles,
          idGenerator: idGenerator,
        ).parsePaths(paths).toList();

    // Get the AST
    final gherkinDocument = envelopes.first.gherkinDocument!;

    // Get the Feature node of the AST
    final feature = gherkinDocument.feature!;
    expect('Minimal', feature.name);

    // Get the first Scenario node of the Feature node
    final scenario = feature.children.first.scenario!;
    expect('minimalistic', scenario.name);
  });

  test('Provides access to pickles which are compiled from the ast', () async {
    const paths = <String>['../testdata/good/scenario_outline.feature'];
    final envelopes =
        await GherkinParser(
          includeSource: false,
          includeGherkinDocument: false,
          idGenerator: idGenerator,
        ).parsePaths(paths).toList();

    // Get the first pickle
    final pickle = envelopes.first.pickle!;

    // Get the first step of the pickle
    final step = pickle.steps.first;
    expect('the minimalism', step.text);
  });

  test('Parses supplied source', () async {
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
          idGenerator: idGenerator,
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

    test('infers the markdown media type from a .md uri', () {
      final envelope = GherkinParser.makeSourceEnvelope('', 'a.md');
      expect(
        envelope.source!.mediaType,
        messages.SourceMediaType.textXCucumberGherkinMarkdown,
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
        mediaType: messages.SourceMediaType.textXCucumberGherkinMarkdown,
      );
      expect(
        envelope.source!.mediaType,
        messages.SourceMediaType.textXCucumberGherkinMarkdown,
      );
    });

    test('an explicit mediaType overrides the uri extension', () {
      final envelope = GherkinParser.makeSourceEnvelope(
        '',
        'a.feature',
        mediaType: messages.SourceMediaType.textXCucumberGherkinMarkdown,
      );
      expect(
        envelope.source!.mediaType,
        messages.SourceMediaType.textXCucumberGherkinMarkdown,
      );
    });
  });
}
