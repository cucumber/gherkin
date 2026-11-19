import 'dart:convert';

import 'package:cucumber_gherkin/src/compile_pickles.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  group('compilePickles', () {
    test('accepts immutable AST collections', () {
      final pickles = compilePickles(_document, 'input.feature', () => 'id');

      expect(pickles, hasLength(1));
      expect(pickles.single.steps, hasLength(1));
    });

    test('input edits and later calls do not change an earlier result', () {
      final input = messages.GherkinDocument.fromJson(_document.toJson());
      final inputBefore = jsonEncode(input);
      final first = compilePickles(input, 'first.feature', () => 'first');
      // JSON maps can retain references to message lists. A string snapshot
      // stays independent even when those lists are subsequently modified.
      final resultBefore = jsonEncode(first);
      expect(jsonEncode(input), inputBefore);

      final scenario = input.feature!.children.single.scenario!;
      final table = scenario.steps.single.dataTable!;
      table.rows.single.cells.clear();
      table.rows.clear();
      scenario.steps.clear();
      scenario.tags.clear();
      input.feature!.children.clear();

      expect(jsonEncode(first), resultBefore);

      compilePickles(
        _document,
        'second.feature',
        () => 'second',
      );

      expect(jsonEncode(first), resultBefore);
    });
  });
}

// A directly constructed AST lets the caller control collection ownership.
const _location = messages.Location(line: 1, column: 1);
const _document = messages.GherkinDocument(
  uri: 'original.feature',
  comments: [],
  feature: messages.Feature(
    location: _location,
    tags: [],
    language: 'en',
    keyword: 'Feature',
    name: 'Ownership',
    description: '',
    children: [
      messages.FeatureChild(
        scenario: messages.Scenario(
          id: 'scenario',
          location: _location,
          tags: [
            messages.Tag(id: 'tag', location: _location, name: '@tag'),
          ],
          keyword: 'Scenario',
          name: 'Collections',
          description: '',
          examples: [],
          steps: [
            messages.Step(
              id: 'step',
              location: _location,
              keyword: 'Given ',
              keywordType: messages.StepKeywordType.context,
              text: 'a table',
              dataTable: messages.DataTable(
                location: _location,
                rows: [
                  messages.TableRow(
                    id: 'row',
                    location: _location,
                    cells: [
                      messages.TableCell(location: _location, value: 'value'),
                    ],
                  ),
                ],
              ),
            ),
          ],
        ),
      ),
    ],
  ),
);
