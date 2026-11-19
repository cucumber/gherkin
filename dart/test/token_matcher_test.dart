import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/gherkin_token_matcher.dart';
import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:cucumber_gherkin/src/language/gherkin_language_keywords.dart';
import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/parser/token.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  late GherkinTokenMatcher matcher;

  setUp(() => matcher = GherkinTokenMatcher(builtinDialects));

  test('switches dialect and reset restores the default', () {
    expect(matcher.matchLanguage(_token('# language: fr')), isTrue);
    final french = _token('  Fonctionnalité: exemple');
    expect(matcher.matchFeatureLine(french), isTrue);
    expect(french.matchedLanguage, 'fr');
    expect(french.matchedText, 'exemple');
    expect(french.location.column, 3);

    matcher.reset();
    expect(
      matcher.matchFeatureLine(_token('Fonctionnalité: exemple')),
      isFalse,
    );
    final english = _token('Feature: example');
    expect(matcher.matchFeatureLine(english), isTrue);
    expect(english.matchedLanguage, 'en');
  });

  test('reports an unknown dialect at the language header', () {
    expect(
      () => matcher.matchLanguage(_token('# language: nonexistent')),
      throwsA(
        isA<NoSuchLanguageException>().having(
          (error) => error.location.line,
          'line',
          1,
        ),
      ),
    );
  });

  group('step keyword categories', () {
    for (final (text, type) in [
      ('Given context', messages.StepKeywordType.context),
      ('When action', messages.StepKeywordType.action),
      ('Then outcome', messages.StepKeywordType.outcome),
      ('And more', messages.StepKeywordType.conjunction),
      ('* anything', messages.StepKeywordType.unknown),
    ]) {
      test('classifies "$text" as ${type.name}', () {
        final step = _token(text);

        expect(matcher.matchStepLine(step), isTrue);
        expect(step.matchedKeywordType, type);
      });
    }

    test('requires the whole keyword', () {
      expect(matcher.matchStepLine(_token('Givenchy')), isFalse);
    });
  });

  test('tracks doc string delimiter and indentation until closing', () {
    final open = _token('  ```text/plain');
    expect(matcher.matchDocStringSeparator(open), isTrue);
    expect(open.matchedText, 'text/plain');
    expect(matcher.matchDocStringSeparator(_token('  """')), isFalse);
    final content = _token(r'    \`\`\`');
    expect(matcher.matchOther(content), isTrue);
    expect(content.matchedText, '  ```');
    expect(matcher.matchDocStringSeparator(_token('  ```')), isTrue);
    final after = _token('    content');
    matcher.matchOther(after);
    expect(after.matchedText, '    content');
  });

  group('reset', () {
    test('discards an unclosed doc string and its indentation', () {
      expect(matcher.matchDocStringSeparator(_token('    ```')), isTrue);

      matcher.reset();

      final content = _token(r'      \"\"\"');
      expect(matcher.matchOther(content), isTrue);
      expect(content.matchedText, r'      \"\"\"');

      final opening = _token('  """text/plain');
      expect(matcher.matchDocStringSeparator(opening), isTrue);
      expect(opening.matchedText, 'text/plain');
      final escaped = _token(r'    \"\"\"');
      expect(matcher.matchOther(escaped), isTrue);
      expect(escaped.matchedText, '  """');
    });

    test('restores a configured non-English default', () {
      final frenchMatcher = GherkinTokenMatcher(builtinDialects, 'fr');
      expect(frenchMatcher.matchLanguage(_token('# language: en')), isTrue);
      expect(frenchMatcher.matchStepLine(_token('Given context')), isTrue);

      frenchMatcher.reset();

      expect(frenchMatcher.matchStepLine(_token('Given context')), isFalse);
      final feature = _token('Fonctionnalité: exemple');
      expect(frenchMatcher.matchFeatureLine(feature), isTrue);
      expect(feature.matchedLanguage, 'fr');
    });
  });

  test('matchers maintain independent language and doc string state', () {
    final other = GherkinTokenMatcher(builtinDialects);
    expect(matcher.matchLanguage(_token('# language: fr')), isTrue);
    expect(matcher.matchDocStringSeparator(_token('    ```')), isTrue);

    final feature = _token('Feature: example');
    expect(other.matchFeatureLine(feature), isTrue);
    expect(feature.matchedLanguage, 'en');
    final opening = _token('"""text/plain');
    expect(other.matchDocStringSeparator(opening), isTrue);
    expect(opening.matchedText, 'text/plain');

    other.reset();

    expect(matcher.matchFeatureLine(_token('Fonctionnalité: exemple')), isTrue);
    final content = _token('      content');
    expect(matcher.matchOther(content), isTrue);
    expect(content.matchedText, '  content');
  });

  group('token reclassification', () {
    for (final (name, text) in [
      ('tags', '  @tag'),
      ('table cells', '  | cell |'),
    ]) {
      test('clears $name when the same token is matched as other', () {
        final token = _token(text);
        final matched = name == 'tags'
            ? matcher.matchTagLine(token)
            : matcher.matchTableRow(token);
        expect(matched, isTrue);
        expect(token.matchedItems, hasLength(1));

        expect(matcher.matchOther(token), isTrue);

        expect(token.matchedType, TokenType.other);
        expect(token.matchedItems, isEmpty);
        expect(token.matchedText, text);
        expect(token.location.column, 1);
      });
    }

    test('clears step metadata when the same token is matched as other', () {
      final token = _token('  Given context');
      expect(matcher.matchStepLine(token), isTrue);
      expect(token.matchedKeyword, 'Given ');
      expect(token.matchedKeywordType, messages.StepKeywordType.context);

      expect(matcher.matchOther(token), isTrue);

      expect(token.matchedKeyword, isEmpty);
      expect(token.matchedKeywordType, isNull);
      expect(token.matchedText, '  Given context');
    });
  });

  group('custom dialects', () {
    test('matches the longest keyword without sorting caller-owned lists', () {
      const given = ['Do ', 'Do more '];
      final custom = GherkinTokenMatcher({'en': _dialect(given: given)});
      final token = _token('Do more work');

      expect(custom.matchStepLine(token), isTrue);

      expect(token.matchedKeyword, 'Do more ');
      expect(token.matchedText, 'work');
      expect(given, ['Do ', 'Do more ']);
    });

    test('keeps shared conjunction keywords unambiguous', () {
      final custom = GherkinTokenMatcher({
        'en': _dialect(and: ['Also '], but: ['Also ']),
      });
      final token = _token('Also work');

      expect(custom.matchStepLine(token), isTrue);
      expect(token.matchedKeywordType, messages.StepKeywordType.conjunction);
    });

    test('rebuilds categories when a keyword changes meaning by dialect', () {
      final custom = GherkinTokenMatcher({
        'en': _dialect(given: ['Do '], when: ['Do ']),
        'other': _dialect(when: ['Do ']),
      });
      final ambiguous = _token('Do work');
      expect(custom.matchStepLine(ambiguous), isTrue);
      expect(ambiguous.matchedKeywordType, messages.StepKeywordType.unknown);

      expect(custom.matchLanguage(_token('# language: other')), isTrue);

      final action = _token('Do work');
      expect(custom.matchStepLine(action), isTrue);
      expect(action.matchedKeywordType, messages.StepKeywordType.action);
    });

    test(
      'rejects an unavailable default dialect without a source location',
      () {
        expect(
          () => GherkinTokenMatcher(const {}, 'missing'),
          throwsA(
            isA<NoSuchLanguageException>().having(
              (error) => error.location,
              'location',
              const messages.Location(line: -1, column: 0),
            ),
          ),
        );
      },
    );
  });
}

Token _token(String text) =>
    Token(GherkinLine(text, 1), const messages.Location(line: 1));

GherkinLanguageKeywords _dialect({
  List<String> given = const [],
  List<String> when = const [],
  List<String> and = const [],
  List<String> but = const [],
}) => GherkinLanguageKeywords(
  'custom',
  'custom',
  const [],
  const [],
  const [],
  const [],
  const [],
  const [],
  given,
  when,
  const [],
  and,
  but,
);
