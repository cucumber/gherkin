import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:cucumber_gherkin/src/parser/token.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  group('ParserException', () {
    test('uses the unknown location when none is provided', () {
      final error = ParserException.create('invalid input');

      expect(error.location.line, -1);
      expect(error.location.column, 0);
      expect(error.message, '(-1,0): invalid input');
      expect(error.toString(), error.message);
    });

    test('formats a line-only location with column zero', () {
      final error = ParserException.create(
        'invalid input',
        const messages.Location(line: 7),
      );

      expect(error.location.column, isNull);
      expect(error.message, '(7:0): invalid input');
    });
  });

  group('UnexpectedTokenException', () {
    test('infers a column from indentation on an unmatched token', () {
      final token = Token(
        GherkinLine('   invalid input  ', 7),
        const messages.Location(line: 7),
      );
      final error = UnexpectedTokenException(token, ['FeatureLine', 'Comment']);

      expect(error.location, const messages.Location(line: 7, column: 4));
      expect(
        error.message,
        "(7:4): expected: FeatureLine, Comment, got 'invalid input'",
      );
      expect(token.location.column, isNull);
    });

    test('preserves an explicit column rather than inferring indentation', () {
      const location = messages.Location(line: 7, column: 2);
      final token = Token(GherkinLine('   invalid', 7), location);
      final error = UnexpectedTokenException(token, ['FeatureLine']);

      expect(error.location, location);
      expect(error.message, "(7:2): expected: FeatureLine, got 'invalid'");
    });
  });

  group('UnexpectedEofException', () {
    test('handles EOF without accessing a source line', () {
      final error = UnexpectedEofException(
        Token.eof(const messages.Location(line: 9)),
        ['StepLine', 'DocStringSeparator'],
      );

      expect(error.location.line, 9);
      expect(error.location.column, isNull);
      expect(
        error.message,
        '(9:0): unexpected end of file, '
        'expected: StepLine, DocStringSeparator',
      );
    });
  });

  group('CompositeParserException', () {
    test('keeps individual locations and diagnostic order', () {
      final errors = [
        ParserException.create(
          'first',
          const messages.Location(line: 2, column: 3),
        ),
        AstBuilderException(
          'second',
          const messages.Location(line: 5, column: 1),
        ),
      ];
      final error = CompositeParserException(errors);

      expect(error.errors, orderedEquals(errors));
      expect(error.location.line, -1);
      expect(
        error.toString(),
        'Parser errors:\n(2:3): first\n(5:1): second',
      );
    });
  });
}
