import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:cucumber_gherkin/cucumber_gherkin.dart';
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
}
