import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:test/test.dart';

void main() {
  test('parses tags and table cells with escaping and whitespace', () {
    final tags = GherkinLine('  @one @two # comment', 4).tags.toList();
    final cells = GherkinLine(
      r'| a\|b | c\\d | e\n | trailing',
      5,
    ).tableCells.toList();

    expect(tags.map((tag) => tag.text), ['@one', '@two']);
    expect(tags.map((tag) => tag.column), [3, 8]);
    expect(cells.map((cell) => cell.text), ['a|b', r'c\d', 'e\n']);
    expect(
      () => GherkinLine('@not valid', 1).tags.toList(),
      throwsA(isA<ParserException>()),
    );
  });

  test('handles indentation bounds and unfinished table cells', () {
    final line = GherkinLine('  text', 1);

    expect(line.getLineText(1), ' text');
    expect(line.getLineText(-1), 'text');
    expect(line.getLineText(3), 'text');
    expect(GherkinLine('| one | unfinished', 1).tableCells.single.text, 'one');
  });
}
