import 'package:cucumber_gherkin/cucumber_gherkin.dart';
import 'package:cucumber_gherkin/src/language/gherkin_line.dart';
import 'package:cucumber_gherkin/src/language/gherkin_line_span.dart';
import 'package:test/test.dart';

void main() {
  const line = 12;

  test('Finds tags', () {
    final gherkinLine = GherkinLine('@this @is @a @tag', line);
    final gherkinLineSpans = gherkinLine.tags;

    expect(const [
      GherkinLineSpan(1, '@this'),
      GherkinLineSpan(7, '@is'),
      GherkinLineSpan(11, '@a'),
      GherkinLineSpan(14, '@tag'),
    ], gherkinLineSpans);
  });

  test('Throws on tags with spaces', () {
    final gherkinLine = GherkinLine('@this @is @a space separated @tag', line);
    expect(
      () => gherkinLine.tags,
      throwsA(const TypeMatcher<ParserException>()),
    );
  });

  test('Throws on tags with leading spaces', () {
    final gherkinLine = GherkinLine('@ leadingSpace', line);
    expect(
      () => gherkinLine.tags,
      throwsA(const TypeMatcher<ParserException>()),
    );
  });

  test('Ignores empty tag', () {
    final gherkinLine = GherkinLine('@', line);
    final gherkinLineSpans = gherkinLine.tags;
    expect(<GherkinLineSpan>[], gherkinLineSpans);
  });

  test('Ignores empty tags', () {
    final gherkinLine = GherkinLine('@@', line);
    final gherkinLineSpans = gherkinLine.tags;
    expect(<GherkinLineSpan>[], gherkinLineSpans);
  });

  test('Finds tags trim whitespace', () {
    final gherkinLine = GherkinLine('    @this @is  @a @tag  ', line);
    final gherkinLineSpans = gherkinLine.tags;
    expect(const [
      GherkinLineSpan(5, '@this'),
      GherkinLineSpan(11, '@is'),
      GherkinLineSpan(16, '@a'),
      GherkinLineSpan(19, '@tag'),
    ], gherkinLineSpans);
  });

  test('Finds tags comment inside tag', () {
    final gherkinLine = GherkinLine('@this @is #acomment  ', line);
    final gherkinLineSpans = gherkinLine.tags;

    expect(const [
      GherkinLineSpan(1, '@this'),
      GherkinLineSpan(7, '@is'),
    ], gherkinLineSpans);
  });

  test('Finds tags commented before tag', () {
    final gherkinLine = GherkinLine('@this @is #@a commented tag', line);
    final gherkinLineSpans = gherkinLine.tags;

    expect(const [
      GherkinLineSpan(1, '@this'),
      GherkinLineSpan(7, '@is'),
    ], gherkinLineSpans);
  });

  test('Finds tags commented multiple tags', () {
    final gherkinLine = GherkinLine(
      '@this @is #@a @commented @sequence of tags',
      line,
    );
    final gherkinLineSpans = gherkinLine.tags;

    expect(const [
      GherkinLineSpan(1, '@this'),
      GherkinLineSpan(7, '@is'),
    ], gherkinLineSpans);
  });

  test('finds_table_cells', () {
    // The cells below has the following whitespace characters on each side:
    // - U+00A0 (non-breaking space)
    // - U+0020 (space)
    // - U+0009 (tab)
    // The input also includes cucumber emoji cells to verify Unicode columns.
    final gherkinLine = GherkinLine(
      '      |  \tred  \t|  \tblue  \t|  \t'
      '\uD83E\uDD52\uD83E\uDD52\uD83E\uDD52  \t|  \tgreen  \t|',
      line,
    );
    final redSpan = gherkinLine.tableCells.first;
    final blueSpan = gherkinLine.tableCells.elementAt(1);
    final emojiSpan = gherkinLine.tableCells.elementAt(2);
    final greenSpan = gherkinLine.tableCells.elementAt(3);

    expect('red', redSpan.text);
    expect(11, redSpan.column);

    expect('blue', blueSpan.text);
    expect(21, blueSpan.column);

    expect('\uD83E\uDD52\uD83E\uDD52\uD83E\uDD52', emojiSpan.text);
    expect(32, emojiSpan.column);

    expect('green', greenSpan.text);
    expect(42, greenSpan.column);
  });

  test('counts_combining_marks_as_separate_columns', () {
    // The first cell holds "cafe" followed by a combining acute accent
    // (U+0301), written as base letter + combining mark. Columns
    // are counted per Unicode code point, so the combining mark advances the
    // column on its own and the next cell starts one column later than it would
    // under grapheme-cluster counting.
    final gherkinLine = GherkinLine('|cafe\u0301|test|', line);

    final firstCell = gherkinLine.tableCells.first;
    final secondCell = gherkinLine.tableCells.elementAt(1);

    expect('cafe\u0301', firstCell.text);
    expect(2, firstCell.column);

    expect('test', secondCell.text);
    // 8 with code-point counting; would be 7 if the combining sequence were
    // counted as a single grapheme cluster.
    expect(8, secondCell.column);
  });

  test('finds_escaped_table_cells', () {
    final gherkinLine = GherkinLine(
      '      | \\|\u00e6\\\\n     | \\o\\no\\  | '
      '\\\\\\|a\\\\\\\\n | \u00f8\\\\\\n\u00f8\\\\|',
      line,
    );

    final texts = gherkinLine.tableCells.map((span) => span.text).toList();
    expect(['|\u00e6\\n', '\\o\no\\', r'\|a\\n', '\u00f8\\\n\u00f8\\'], texts);
  });

  test('preserve_escaped_new_lines_at_start_and_end', () {
    final gherkinLine = GherkinLine(
      '      |  \nraindrops--\nher last kiss\ngoodbye.\n  |',
      line,
    );
    final texts = gherkinLine.tableCells.map((span) => span.text).toList();
    expect(['\nraindrops--\nher last kiss\ngoodbye.\n'], texts);
  });

  test('escapes_backslash', () {
    final gherkinLine = GherkinLine(r'|\\o\no\||', line);
    final texts = gherkinLine.tableCells.map((span) => span.text).toList();
    expect(['\\o\no|'], texts);
  });

  test('throws_on_illegal_escapes_backslash', () {
    final gherkinLine = GherkinLine(r'|\o\no\||', line);
    final texts = gherkinLine.tableCells.map((span) => span.text).toList();
    expect(['\\o\no|'], texts);
  });
}
