import 'dart:io';

import 'package:cucumber_gherkin/cucumber_gherkin.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  test('compiles backgrounds, rules, outlines, tags, and step types', () {
    final pickles = _pickles(_fixture('complex_background.feature'));

    expect(pickles, hasLength(4));
    expect(pickles[0].steps, hasLength(2));
    expect(pickles[2].steps.map((step) => step.text), [
      'the minimalism inside a background',
      'a rule background step',
      'the 1 minimalism',
    ]);
    expect(pickles[2].steps.first.type, messages.PickleStepType.context);
    expect(pickles[2].astNodeIds, hasLength(2));
  });

  test('interpolates scenario outline names, tables, and doc strings', () {
    final pickles = _pickles(_fixture('example_tokens_everywhere.feature'));

    expect(pickles.map((pickle) => pickle.name), ['the un', 'the uno']);
    expect(pickles.first.steps[0].argument!.docString!.content, 'trois');
    expect(
      pickles
          .first
          .steps[1]
          .argument!
          .dataTable!
          .rows
          .single
          .cells
          .single
          .value,
      'cinq',
    );
  });

  test('preserves argument order when a step has a table and doc string', () {
    final pickles = _pickles(
      _fixture('step_with_datatable_and_docstring.feature'),
    );

    expect(pickles[0].steps.single.argument!.dataTable!.argumentIndex, 1);
    expect(pickles[0].steps.single.argument!.docString!.argumentIndex, 2);
    expect(pickles[1].steps.single.argument!.dataTable!.argumentIndex, 2);
    expect(pickles[1].steps.single.argument!.docString!.argumentIndex, 1);
  });

  test('does not create pickles for a document without a feature', () {
    expect(_pickles('# only a comment\n'), isEmpty);
  });
}

String _fixture(String name) =>
    File('../testdata/good/$name').readAsStringSync();

List<messages.Pickle> _pickles(String source) => generateMessages(
  source,
  'fixture.feature',
  const GherkinOptions(includeSource: false, includeGherkinDocument: false),
).map((envelope) => envelope.pickle).whereType<messages.Pickle>().toList();
