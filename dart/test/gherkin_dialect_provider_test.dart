import 'package:gherkin/exceptions.dart';
import 'package:gherkin/language.dart';
import 'package:test/test.dart';

void main() {
  final languages0 = loadGherkinLanguagesFromJsonAsset();

  test('Provides emoji dialect', () {
    var em = GherkinDialectProvider(languages0).getDialect('em');
    var scenarioKeywords = em.scenarioKeywords[0];
    var length = scenarioKeywords.runes.length;
    expect(length, 1);
  });

  test('Provides language list', () {
    var languages = GherkinDialectProvider(languages0).languages;
    expect(languages.contains('en'), isTrue);
  });

  test(
    'Provides native name which is used in cucumber jvm code generation',
    () {
      var no = GherkinDialectProvider(languages0).getDialect('no');
      expect(no.nativeName, 'norsk');
    },
  );

  test('Should throw NoSuchLanguageException for invalid language', () {
    var provider = GherkinDialectProvider(languages0);
    expect(
      () => provider.getDialect('nosuchlang', Location(1, 2)),
      throwsA(TypeMatcher<NoSuchLanguageException>()),
    );
  });

  test('Should throw NoSuchLanguageException for invalid default language', () {
    var provider = GherkinDialectProvider(languages0, 'nosuchlang');
    expect(
      () => provider.defaultDialect,
      throwsA(TypeMatcher<NoSuchLanguageException>()),
    );
  });

  test(
    'Should throw NoSuchLanguageException for invalid language without location',
    () {
      var provider = GherkinDialectProvider(languages0);
      expect(
        () => provider.getDialect('nosuchlang'),
        throwsA(TypeMatcher<NoSuchLanguageException>()),
      );
    },
  );
}
