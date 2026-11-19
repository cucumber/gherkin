import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/gherkin_token_matcher.dart';
import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:cucumber_gherkin/src/parser/token.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

Token token(String text) =>
    Token(GherkinLine(text, 1), const messages.Location(line: 1));

void main() {
  late GherkinTokenMatcher matcher;

  setUp(() => matcher = GherkinTokenMatcher(builtinDialects));

  test('switches dialect and reset restores the default', () {
    expect(matcher.matchLanguage(token('# language: fr')), isTrue);
    final french = token('  Fonctionnalité: exemple');
    expect(matcher.matchFeatureLine(french), isTrue);
    expect(french.matchedLanguage, 'fr');
    expect(french.matchedText, 'exemple');
    expect(french.location.column, 3);

    matcher.reset();
    expect(matcher.matchFeatureLine(token('Fonctionnalité: exemple')), isFalse);
    final english = token('Feature: example');
    expect(matcher.matchFeatureLine(english), isTrue);
    expect(english.matchedLanguage, 'en');
  });

  test('reports an unknown dialect at the language header', () {
    expect(
      () => matcher.matchLanguage(token('# language: nonexistent')),
      throwsA(
        isA<NoSuchLanguageException>().having(
          (error) => error.location.line,
          'line',
          1,
        ),
      ),
    );
  });

  test('matches step keyword categories, including ambiguous wildcard', () {
    for (final (text, type) in [
      ('Given context', messages.StepKeywordType.context),
      ('When action', messages.StepKeywordType.action),
      ('Then outcome', messages.StepKeywordType.outcome),
      ('And more', messages.StepKeywordType.conjunction),
      ('* anything', messages.StepKeywordType.unknown),
    ]) {
      final step = token(text);
      expect(matcher.matchStepLine(step), isTrue, reason: text);
      expect(step.matchedKeywordType, type, reason: text);
    }
    expect(matcher.matchStepLine(token('Givenchy')), isFalse);
  });

  test('tracks doc string delimiter and indentation until closing', () {
    final open = token('  ```text/plain');
    expect(matcher.matchDocStringSeparator(open), isTrue);
    expect(open.matchedText, 'text/plain');
    expect(matcher.matchDocStringSeparator(token('  """')), isFalse);
    final content = token(r'    \`\`\`');
    expect(matcher.matchOther(content), isTrue);
    expect(content.matchedText, '  ```');
    expect(matcher.matchDocStringSeparator(token('  ```')), isTrue);
    final after = token('    content');
    matcher.matchOther(after);
    expect(after.matchedText, '    content');
  });

  group('reset', () {
    test('discards an unclosed doc string and its indentation', () {
      expect(matcher.matchDocStringSeparator(token('    ```')), isTrue);

      matcher.reset();

      final content = token(r'      \"\"\"');
      expect(matcher.matchOther(content), isTrue);
      expect(content.matchedText, r'      \"\"\"');

      final opening = token('  """text/plain');
      expect(matcher.matchDocStringSeparator(opening), isTrue);
      expect(opening.matchedText, 'text/plain');
      final escaped = token(r'    \"\"\"');
      expect(matcher.matchOther(escaped), isTrue);
      expect(escaped.matchedText, '  """');
    });

    test('restores a configured non-English default', () {
      final frenchMatcher = GherkinTokenMatcher(builtinDialects, 'fr');
      expect(frenchMatcher.matchLanguage(token('# language: en')), isTrue);
      expect(frenchMatcher.matchStepLine(token('Given context')), isTrue);

      frenchMatcher.reset();

      expect(frenchMatcher.matchStepLine(token('Given context')), isFalse);
      final feature = token('Fonctionnalité: exemple');
      expect(frenchMatcher.matchFeatureLine(feature), isTrue);
      expect(feature.matchedLanguage, 'fr');
    });
  });

  test('matchers maintain independent language and doc string state', () {
    final other = GherkinTokenMatcher(builtinDialects);
    expect(matcher.matchLanguage(token('# language: fr')), isTrue);
    expect(matcher.matchDocStringSeparator(token('    ```')), isTrue);

    final feature = token('Feature: example');
    expect(other.matchFeatureLine(feature), isTrue);
    expect(feature.matchedLanguage, 'en');
    final opening = token('"""text/plain');
    expect(other.matchDocStringSeparator(opening), isTrue);
    expect(opening.matchedText, 'text/plain');

    other.reset();

    expect(matcher.matchFeatureLine(token('Fonctionnalité: exemple')), isTrue);
    final content = token('      content');
    expect(matcher.matchOther(content), isTrue);
    expect(content.matchedText, '  content');
  });
}
