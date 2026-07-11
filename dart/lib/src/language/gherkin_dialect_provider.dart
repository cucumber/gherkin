import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/language/gherkin_dialect.dart';
import 'package:cucumber_gherkin/src/language/gherkin_language_keywords.dart';
import 'package:cucumber_gherkin/src/language/location.dart';

/// Supplies [GherkinDialect]s by language tag, backed by an in-memory map of
/// dialects.
class GherkinDialectProvider {
  /// Creates a provider over [_dialects], defaulting to [_defaultDialectName].
  GherkinDialectProvider(this._dialects, [this._defaultDialectName = 'en']);

  final String _defaultDialectName;
  final Map<String, GherkinLanguageKeywords> _dialects;

  /// Caches the [GherkinDialect] built for each language tag so derived
  /// keyword lists are reused across matcher resets.
  final Map<String, GherkinDialect> _dialectCache = <String, GherkinDialect>{};

  /// The dialect used when none is specified.
  GherkinDialect get defaultDialect => getDialect(_defaultDialectName);

  /// Returns the dialect for [language].
  ///
  /// [location] is used to report a [NoSuchLanguageException] when the language
  /// is not supported.
  GherkinDialect getDialect(
    String language, [
    Location location = Location.empty,
  ]) {
    final cached = _dialectCache[language];
    if (cached != null) {
      return cached;
    }
    final languageSettings = _dialects[language];
    if (languageSettings == null) {
      throw NoSuchLanguageException(language, location);
    }
    return _dialectCache[language] = GherkinDialect(language, languageSettings);
  }
}
