import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/gherkin_token_matcher.dart';
import 'package:cucumber_gherkin/src/language/gherkin_language_keywords.dart';
import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:cucumber_gherkin/src/parser/token.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  test(
    'matches syntax, resets state, and gives precedence to long keywords',
    () {
      final matcher = GherkinTokenMatcher(<String, GherkinLanguageKeywords>{
        'en': _keywords(given: ['Given ', 'Given long ']),
        'fr': _keywords(feature: ['Fonctionnalite'], given: ['Soit ']),
      });
      final feature = _token('Feature: title');
      final step = _token('Given long text');
      final docString = _token('  """json');

      expect(matcher.matchFeatureLine(feature), isTrue);
      expect(feature.matchedLanguage, 'en');
      expect(matcher.matchStepLine(step), isTrue);
      expect(step.matchedKeyword, 'Given long ');
      expect(step.matchedText, 'text');
      expect(matcher.matchDocStringSeparator(docString), isTrue);
      expect(matcher.matchOther(_token(r'  \"\"\"')), isTrue);
      expect(matcher.matchDocStringSeparator(_token('  """')), isTrue);
      expect(matcher.matchTagLine(_token('@tag')), isTrue);
      expect(matcher.matchTableRow(_token('| cell |')), isTrue);
      expect(
        matcher.matchEOF(Token.eof(const messages.Location(line: 2))),
        isTrue,
      );
      expect(matcher.matchEmpty(_token('text')), isFalse);
      expect(matcher.matchComment(_token('text')), isFalse);
      matcher.reset();
      expect(matcher.matchLanguage(_token('# language: fr')), isTrue);
      expect(matcher.matchFeatureLine(_token('Fonctionnalite: titre')), isTrue);
    },
  );

  test('rejects unknown languages and marks ambiguous keywords as unknown', () {
    final matcher = GherkinTokenMatcher(<String, GherkinLanguageKeywords>{
      'en': _keywords(given: ['* '], when: ['* ']),
    });
    final ambiguousStep = _token('* a step');

    expect(matcher.matchStepLine(ambiguousStep), isTrue);
    expect(ambiguousStep.matchedKeywordType, messages.StepKeywordType.unknown);
    expect(
      () => matcher.matchLanguage(_token('# language: missing')),
      throwsA(isA<NoSuchLanguageException>()),
    );
  });
}

Token _token(String text, {int line = 1}) =>
    Token(GherkinLine(text, line), messages.Location(line: line));

GherkinLanguageKeywords _keywords({
  List<String> feature = const ['Feature'],
  List<String> given = const ['Given '],
  List<String> when = const ['When '],
}) => GherkinLanguageKeywords(
  'English',
  'English',
  feature,
  const ['Rule'],
  const ['Background'],
  const ['Scenario'],
  const ['Scenario Outline'],
  const ['Examples'],
  given,
  when,
  const ['Then '],
  const ['And '],
  const ['But '],
);
