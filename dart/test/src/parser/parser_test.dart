import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:cucumber_gherkin/exceptions.dart';
import 'package:cucumber_gherkin/language.dart';
import 'package:cucumber_gherkin/src/ast/messages_gherkin_document_builder.dart';
import 'package:cucumber_gherkin/src/language/gherkin_languages_loader.dart';
import 'package:cucumber_gherkin/src/language/gherkin_token_matcher.dart';
import 'package:cucumber_gherkin/src/gherkin/id_generator.dart';
import 'package:cucumber_gherkin/src/language/string_token_scanner.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:test/test.dart';

/// Parses [source] with a fresh Berp-generated [Parser] and returns the
/// resulting [messages.GherkinDocument].
messages.GherkinDocument _parse(
  String source, {
  String defaultDialect = 'en',
  bool stopAtFirstError = false,
}) {
  final languages = loadGherkinLanguagesFromJsonAsset();
  final dialectProvider = GherkinDialectProvider(languages, defaultDialect);
  final matcher = GherkinTokenMatcher(dialectProvider);
  final builder = MessagesGherkinDocumentBuilder(
    IdGenerator.incrementingGenerator,
  );
  final parser = Parser<messages.GherkinDocument>(builder)
    ..stopAtFirstError = stopAtFirstError;
  return parser.parse(StringTokenScanner(source), matcher);
}

void main() {
  test('Change default language', () {
    final gherkinDocument = _parse(
      'Egenskap: i18n support\n',
      defaultDialect: 'no',
    );

    expect(gherkinDocument.feature!.language, 'no');
  });

  test('parses a feature with a background and a scenario', () {
    final gherkinDocument = _parse('''
Feature: Guess the word

  Background:
    Given a started game

  Scenario: Maker starts a game
    When the Maker starts a game
    Then the Maker waits for a Breaker to join
''');

    final feature = gherkinDocument.feature!;
    expect(feature.keyword, 'Feature');
    expect(feature.name, 'Guess the word');
    expect(feature.children, hasLength(2));

    final background = feature.children.first.background!;
    expect(background.keyword, 'Background');
    expect(background.steps, hasLength(1));

    final scenario = feature.children.last.scenario!;
    expect(scenario.keyword, 'Scenario');
    expect(scenario.name, 'Maker starts a game');
    expect(scenario.steps, hasLength(2));
    expect(scenario.steps.map((s) => s.text), [
      'the Maker starts a game',
      'the Maker waits for a Breaker to join',
    ]);
  });

  test('parses a scenario outline with an examples table', () {
    final gherkinDocument = _parse('''
Feature: Eating

  Scenario Outline: eating
    Given there are <start> cucumbers
    When I eat <eat> cucumbers
    Then I should have <left> cucumbers

    Examples:
      | start | eat | left |
      |    12 |   5 |    7 |
      |    20 |   5 |   15 |
''');

    final scenario = gherkinDocument.feature!.children.single.scenario!;
    expect(scenario.keyword, 'Scenario Outline');
    expect(scenario.steps, hasLength(3));

    final examples = scenario.examples.single;
    expect(examples.tableHeader!.cells.map((c) => c.value), [
      'start',
      'eat',
      'left',
    ]);
    expect(examples.tableBody, hasLength(2));
    expect(examples.tableBody.first.cells.map((c) => c.value), [
      '12',
      '5',
      '7',
    ]);
  });

  test('collects multiple parse errors when stopAtFirstError is false', () {
    // A tag line where a scenario/feature line is expected produces an error.
    expect(
      () => _parse('invalid line 1\ninvalid line 2\n'),
      throwsA(
        isA<CompositeParserException>().having(
          (e) => e.errors.length,
          'errors.length',
          greaterThanOrEqualTo(1),
        ),
      ),
    );
  });

  test('throws the first error immediately when stopAtFirstError is true', () {
    expect(
      () => _parse('@tag\nnot a feature line\n', stopAtFirstError: true),
      throwsA(isA<ParserException>()),
    );
  });

  test('a parser instance can be reused for multiple documents', () {
    final languages = loadGherkinLanguagesFromJsonAsset();
    final dialectProvider = GherkinDialectProvider(languages, 'en');
    final matcher = GherkinTokenMatcher(dialectProvider);
    final builder = MessagesGherkinDocumentBuilder(
      IdGenerator.incrementingGenerator,
    );
    final parser = Parser<messages.GherkinDocument>(builder);

    final first = parser.parse(StringTokenScanner('Feature: One\n'), matcher);
    final second = parser.parse(StringTokenScanner('Feature: Two\n'), matcher);

    expect(first.feature!.name, 'One');
    expect(second.feature!.name, 'Two');
  });
}
