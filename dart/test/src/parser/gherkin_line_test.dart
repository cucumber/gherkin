import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:test/test.dart';

void main() {
  group('GherkinLine.getLineText', () {
    test('preserves the source text when no indentation is requested', () {
      final line = GherkinLine('  text  ', 1);

      expect(line.getLineText(), '  text  ');
    });

    for (final (indent, expected) in [
      (0, '  text  '),
      (1, ' text  '),
      (2, 'text  '),
    ]) {
      test('removes $indent leading characters', () {
        final line = GherkinLine('  text  ', 1);

        expect(line.getLineText(indent), expected);
      });
    }

    for (final indent in [-1, 3]) {
      test('left-trims for out-of-range indentation $indent', () {
        final line = GherkinLine('  text  ', 1);

        expect(line.getLineText(indent), 'text  ');
      });
    }
  });
}
