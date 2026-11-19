import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/gherkin_token_matcher.dart';
import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:cucumber_gherkin/src/language/gherkin_language_keywords.dart';
import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:cucumber_gherkin/src/parser/token.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  group('GherkinTokenMatcher.reset', () {
    for (final (language, feature, otherLanguage, otherFeature) in [
      ('en', 'Feature: example', 'fr', 'Fonctionnalité: exemple'),
      ('fr', 'Fonctionnalité: exemple', 'en', 'Feature: example'),
    ]) {
      test('restores the configured $language dialect', () {
        final matcher = GherkinTokenMatcher(builtinDialects, language);
        expect(
          matcher.matchLanguage(_token('# language: $otherLanguage')),
          isTrue,
        );
        expect(matcher.matchFeatureLine(_token(otherFeature)), isTrue);

        matcher.reset();

        expect(matcher.matchFeatureLine(_token(otherFeature)), isFalse);
        final token = _token(feature);
        expect(matcher.matchFeatureLine(token), isTrue);
        expect(token.matchedLanguage, language);
      });
    }

    test('discards an unclosed doc string and its indentation', () {
      final matcher = GherkinTokenMatcher(builtinDialects);
      expect(matcher.matchDocStringSeparator(_token('    ```')), isTrue);

      matcher.reset();

      final content = _token(r'      \`\`\`');
      expect(matcher.matchOther(content), isTrue);
      expect(content.matchedText, r'      \`\`\`');
      expect(matcher.matchDocStringSeparator(_token('"""')), isTrue);
    });
  });

  group('GherkinTokenMatcher instance isolation', () {
    test('changing and resetting one dialect leaves the other intact', () {
      final first = GherkinTokenMatcher(builtinDialects);
      final second = GherkinTokenMatcher(builtinDialects);
      expect(first.matchLanguage(_token('# language: fr')), isTrue);
      expect(second.matchFeatureLine(_token('Feature: example')), isTrue);

      second.reset();

      final feature = _token('Fonctionnalité: exemple');
      expect(first.matchFeatureLine(feature), isTrue);
      expect(feature.matchedLanguage, 'fr');
    });

    test('doc string delimiters and indentation belong to each matcher', () {
      final first = GherkinTokenMatcher(builtinDialects);
      final second = GherkinTokenMatcher(builtinDialects);
      expect(first.matchDocStringSeparator(_token('    ```')), isTrue);
      expect(second.matchDocStringSeparator(_token('"""')), isTrue);

      second.reset();

      final content = _token('      content');
      expect(first.matchOther(content), isTrue);
      expect(content.matchedText, '  content');
      expect(first.matchDocStringSeparator(_token('"""')), isFalse);
    });
  });

  group('GherkinTokenMatcher custom dialects', () {
    test('accepts immutable keyword lists in caller-supplied order', () {
      final matcher = GherkinTokenMatcher({
        'en': _dialect(given: const ['Do ', 'Do more ']),
      });
      final token = _token('Do more work');

      expect(matcher.matchStepLine(token), isTrue);

      expect(token.matchedKeyword, 'Do more ');
      expect(token.matchedText, 'work');
    });

    test('keeps shared conjunction keywords unambiguous', () {
      final matcher = GherkinTokenMatcher({
        'en': _dialect(and: ['Also '], but: ['Also ']),
      });
      final token = _token('Also work');

      expect(matcher.matchStepLine(token), isTrue);

      expect(token.matchedKeywordType, messages.StepKeywordType.conjunction);
    });

    test('rebuilds categories when a keyword changes meaning by dialect', () {
      final matcher = GherkinTokenMatcher({
        'en': _dialect(given: ['Do '], when: ['Do ']),
        'other': _dialect(when: ['Do ']),
      });
      final ambiguous = _token('Do work');
      expect(matcher.matchStepLine(ambiguous), isTrue);
      expect(ambiguous.matchedKeywordType, messages.StepKeywordType.unknown);

      expect(matcher.matchLanguage(_token('# language: other')), isTrue);

      final action = _token('Do work');
      expect(matcher.matchStepLine(action), isTrue);
      expect(action.matchedKeywordType, messages.StepKeywordType.action);
    });

    test('rejects an unavailable default without a source location', () {
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
    });
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
