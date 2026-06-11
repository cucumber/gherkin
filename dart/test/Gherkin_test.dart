import 'package:gherkin/gherkin.dart';
import 'package:gherkin/language.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  final idGenerator = IdGenerator.incrementingGenerator;

  test('Use this in readme', () async {
    final paths = const <String>['../testdata/good/minimal.feature'];
    final includeSource = false;
    final includeAst = true;
    final includePickles = true;
    final envelopeStream = Gherkin.fromPaths(
      paths,
      includeSource,
      includeAst,
      includePickles,
      idGenerator,
    );

    final pickleStream = envelopeStream.where(
      (envelope) => envelope.pickle != null,
    );

    final envelope = await pickleStream.first;
    expect('minimalistic', envelope.pickle!.name);
  });

  test('Provides access to the ast', () async {
    final paths = const <String>['../testdata/good/minimal.feature'];
    final includeSource = false;
    final includeAst = true;
    final includePickles = false;
    final envelopes =
        await Gherkin.fromPaths(
          paths,
          includeSource,
          includeAst,
          includePickles,
          idGenerator,
        ).toList();

    // Get the AST
    var gherkinDocument = envelopes.first.gherkinDocument!;

    // Get the Feature node of the AST
    var feature = gherkinDocument.feature!;
    expect('Minimal', feature.name);

    // Get the first Scenario node of the Feature node
    var scenario = feature.children.first.scenario!;
    expect('minimalistic', scenario.name);
  });

  test('Provides access to pickles which are compiled from the ast', () async {
    final paths = const <String>['../testdata/good/scenario_outline.feature'];
    final envelopes =
        await Gherkin.fromPaths(
          paths,
          false,
          false,
          true,
          idGenerator,
        ).toList();

    // Get the first pickle
    final pickle = envelopes.first.pickle!;

    // Get the first step of the pickle
    final step = pickle.steps.first;
    expect('the minimalism', step.text);
  });

  test('Parses supplied source', () async {
    final envelope = Gherkin.makeSourceEnvelope(
      'Feature: Minimal\n'
          '\n'
          '  Scenario: minimalistic\n'
          '    Given the minimalism\n',
      'test.feature',
    );

    final singletonList = <messages.Envelope>[envelope];

    final envelopes =
        await Gherkin.fromSources(
          singletonList,
          false,
          true,
          false,
          idGenerator,
        ).toList();

    final gherkinDocument = envelopes.first.gherkinDocument!;
    final feature = gherkinDocument.feature!;
    expect('Minimal', feature.name);
  });
}
