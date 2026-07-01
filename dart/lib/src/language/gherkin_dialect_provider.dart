import 'package:cucumber_gherkin/exceptions.dart';
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
    if (!_dialects.containsKey(language)) {
      throw NoSuchLanguageException(language, location);
    }
    final languageSettings =
        _dialects[language] ?? GherkinLanguageKeywords.empty;
    return GherkinDialect(language, languageSettings);
  }

  /// The language tags of all supported dialects.
  List<String> get languages => _dialects.keys.toList();
}
