import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/language/gherkin_language_keywords.dart';
import 'package:cucumber_gherkin/src/language/location.dart';

/// Supplies [GherkinLanguageKeywords] by language tag.
class GherkinDialectProvider {
  /// Creates a provider over [_dialects], defaulting to [_defaultLanguage].
  GherkinDialectProvider(this._dialects, [this._defaultLanguage = 'en']);

  final String _defaultLanguage;
  final Map<String, GherkinLanguageKeywords> _dialects;

  /// The language tag used when none is specified.
  String get defaultLanguage => _defaultLanguage;

  /// The keywords for [defaultLanguage].
  GherkinLanguageKeywords get defaultKeywords => getKeywords(_defaultLanguage);

  /// Returns the keywords for [language].
  ///
  /// [location] is used to report a [NoSuchLanguageException] when the language
  /// is not supported.
  GherkinLanguageKeywords getKeywords(
    String language, [
    Location location = Location.empty,
  ]) {
    final keywords = _dialects[language];
    if (keywords == null) {
      throw NoSuchLanguageException(language, location);
    }
    return keywords;
  }
}
