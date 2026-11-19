import 'package:cucumber_gherkin/src/compile_pickles.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  group('compilePickles', () {
    test('accepts immutable AST collections without modifying them', () {
      final before = _document.toJson();

      final pickles = compilePickles(_document, 'input.feature', () => 'id');

      expect(pickles, hasLength(1));
      expect(pickles.single.steps, hasLength(1));
      expect(_document.toJson(), before);
    });

    test('result collections are independent of the AST and later calls', () {
      final first = compilePickles(_document, 'first.feature', () => 'first');
      final second = compilePickles(
        _document,
        'second.feature',
        () => 'second',
      );
      final original = _document.toJson();
      final secondBefore = second.single.toJson();
      final pickle = first.single;
      final step = pickle.steps.single;
      final table = step.argument!.dataTable!;

      table.rows.single.cells.clear();
      table.rows.clear();
      step.astNodeIds.clear();
      pickle.steps.clear();
      pickle.tags.clear();
      pickle.astNodeIds.clear();
      first.clear();

      expect(_document.toJson(), original);
      expect(second.single.toJson(), secondBefore);
    });

    test('uses the URI and ID generator supplied to each invocation', () {
      var nextId = 0;
      final first = compilePickles(
        _document,
        'first.feature',
        () => 'first-${nextId++}',
      ).single;
      final second = compilePickles(
        _document,
        'second.feature',
        () => 'second-${nextId++}',
      ).single;

      expect(first.uri, 'first.feature');
      expect(second.uri, 'second.feature');
      expect(first.steps.single.id, 'first-0');
      expect(first.id, 'first-1');
      expect(second.steps.single.id, 'second-2');
      expect(second.id, 'second-3');
      expect(nextId, 4);
    });

    test('propagates ID generator failures without changing the AST', () {
      final failure = StateError('ID allocation failed');
      final before = _document.toJson();

      expect(
        () => compilePickles(
          _document,
          'input.feature',
          () => throw failure,
        ),
        throwsA(same(failure)),
      );
      expect(_document.toJson(), before);
    });
  });
}

// Construct the input directly: these tests concern Dart object ownership and
// injected dependencies, rather than parsing or feature-to-pickle semantics.
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
