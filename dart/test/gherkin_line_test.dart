import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:test/test.dart';

void main() {
  test('removes requested indentation or trims when out of range', () {
    final line = GherkinLine('  Feature: example  ', 4);
    expect(line.indent, 2);
    expect(line.getLineText(), '  Feature: example  ');
    expect(line.getLineText(1), ' Feature: example  ');
    expect(line.getLineText(-1), 'Feature: example  ');
    expect(line.getLineText(3), 'Feature: example  ');
    expect(line.startsWithTitleKeyword('Feature'), isTrue);
    expect(line.getRestTrimmed('Feature:'.length), 'example');
    expect(GherkinLine(' \t', 1).isEmptyLine, isTrue);
  });

  test('extracts tags with columns and ignores trailing comments', () {
    final tags = GherkinLine('  @one @two # comment', 3).tags.toList();
    expect(tags.map((tag) => tag.text), ['@one', '@two']);
    expect(tags.map((tag) => tag.column), [3, 8]);
  });

  test('rejects whitespace within a tag at its source location', () {
    expect(
      () => GherkinLine('  @bad tag', 7).tags,
      throwsA(
        isA<ParserException>()
            .having((error) => error.location.line, 'line', 7)
            .having((error) => error.location.column, 'column', 3)
            .having(
              (error) => error.message,
              'message',
              contains('whitespace'),
            ),
      ),
    );
  });

  test('unescapes table cells and preserves unknown escape sequences', () {
    final cells = GherkinLine(
      r' | a\|b | c\nx | d\\e | \q |',
      1,
    ).tableCells.toList();
    expect(cells.map((cell) => cell.text), ['a|b', 'c\nx', r'd\e', r'\q']);
    expect(cells.first.column, 4);
  });
}
