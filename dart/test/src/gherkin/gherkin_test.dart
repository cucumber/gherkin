import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:cucumber_gherkin/cucumber_gherkin_io.dart';
import 'package:test/test.dart';

void main() {
  final idGenerator = IdGenerator.incrementingGenerator;

  test('Use this in readme', () async {
    const paths = <String>['../testdata/good/minimal.feature'];
    const includeSource = false;
    const includeGherkinDocument = true;
    const includePickles = true;
    final envelopeStream = GherkinParser(
      includeSource: includeSource,
      includeGherkinDocument: includeGherkinDocument,
      includePickles: includePickles,
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
    const includeGherkinDocument = true;
    const includePickles = false;
    final envelopes =
        await GherkinParser(
          includeSource: includeSource,
          includeGherkinDocument: includeGherkinDocument,
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
          includePickles: true,
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
          includeGherkinDocument: true,
          includePickles: false,
          idGenerator: idGenerator,
        ).parseEnvelopes(Stream.fromIterable(singletonList)).toList();

    final gherkinDocument = envelopes.first.gherkinDocument!;
    final feature = gherkinDocument.feature!;
    expect('Minimal', feature.name);
  });

  group('convenience methods', () {
    const feature =
        'Feature: Minimal\n'
        '\n'
        '  Scenario: minimalistic\n'
        '    Given the minimalism\n';

    GherkinParser parser() => GherkinParser(idGenerator: idGenerator);

    test('parseStringSync returns the document (default uri)', () {
      final document = parser().parseStringSync(feature);
      expect(document.feature!.name, 'Minimal');
      expect(document.uri, GherkinParser.defaultUri);
    });

    test('parseStringSync uses an explicit uri', () {
      final document = parser().parseStringSync(feature, uri: 'a.feature');
      expect(document.uri, 'a.feature');
    });

    test('compileStringSync returns the pickles', () {
      final pickles = parser().compileStringSync(feature);
      expect(pickles, hasLength(1));
      expect(pickles.single.name, 'minimalistic');
    });

    test('parseStringSync throws a ParserException on malformed input', () {
      expect(
        () => parser().parseStringSync('not gherkin'),
        throwsA(isA<ParserException>()),
      );
    });

    test('compileStringSync throws a ParserException on malformed input', () {
      expect(
        () => parser().compileStringSync('not gherkin'),
        throwsA(isA<ParserException>()),
      );
    });

    test('parseDocument reads a file and returns the document', () async {
      final document = await parser().parseDocument(
        '../testdata/good/minimal.feature',
      );
      expect(document.feature!.name, 'Minimal');
      expect(document.uri, '../testdata/good/minimal.feature');
    });

    test('compilePickles reads a file and returns the pickles', () async {
      final pickles = await parser().compilePickles(
        '../testdata/good/minimal.feature',
      );
      expect(pickles.single.name, 'minimalistic');
    });

    test('parseDocument throws a GherkinException on a missing file', () {
      expect(
        parser().parseDocument('does-not-exist.feature'),
        throwsA(isA<GherkinException>()),
      );
    });
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

    test('throws GherkinException for an unrecognized extension with no '
        'mediaType', () {
      expect(
        () => GherkinParser.makeSourceEnvelope('', 'a.txt'),
        throwsA(isA<GherkinException>()),
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
