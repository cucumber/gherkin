import 'package:cucumber_gherkin/exceptions.dart';
import 'package:cucumber_gherkin/language.dart';
import 'package:cucumber_gherkin/src/language/gherkin_languages_loader.dart';
import 'package:cucumber_gherkin/src/language/location.dart';
import 'package:test/test.dart';

void main() {
  final languages0 = builtinGherkinDialects();

  test('Provides emoji dialect', () {
    final em = GherkinDialectProvider(languages0).getDialect('em');
    final scenarioKeywords = em.scenarioKeywords[0];
    final length = scenarioKeywords.runes.length;
    expect(length, 1);
  });

  test('Provides language list', () {
    final languages = GherkinDialectProvider(languages0).languages;
    expect(languages.contains('en'), isTrue);
  });

  test(
    'Provides native name which is used in cucumber jvm code generation',
    () {
      final no = GherkinDialectProvider(languages0).getDialect('no');
      expect(no.nativeName, 'norsk');
    },
  );

  test('Should throw NoSuchLanguageException for invalid language', () {
    final provider = GherkinDialectProvider(languages0);
    expect(
      () => provider.getDialect('nosuchlang', const Location(1, 2)),
      throwsA(const TypeMatcher<NoSuchLanguageException>()),
    );
  });

  test('Should throw NoSuchLanguageException for invalid default language', () {
    final provider = GherkinDialectProvider(languages0, 'nosuchlang');
    expect(
      () => provider.defaultDialect,
      throwsA(const TypeMatcher<NoSuchLanguageException>()),
    );
  });

  test('Should throw NoSuchLanguageException for invalid language '
      'without location', () {
    final provider = GherkinDialectProvider(languages0);
    expect(
      () => provider.getDialect('nosuchlang'),
      throwsA(const TypeMatcher<NoSuchLanguageException>()),
    );
  });
}
