import 'dart:convert';
import 'dart:io';

import 'package:gherkin/exceptions.dart';
import 'package:gherkin/language.dart';
import 'package:gherkin/src/language/gherkin_language_keywords.dart';
import 'package:path/path.dart';

/// An [IGherkinDialectProvider] backed by an in-memory map of dialects.
class GherkinDialectProvider implements IGherkinDialectProvider {
  /// Creates a provider over [_dialects], defaulting to [_defaultDialectName].
  GherkinDialectProvider(this._dialects, [this._defaultDialectName = 'en']);

  final String _defaultDialectName;
  final Map<String, GherkinLanguageKeywords> _dialects;

  @override
  IGherkinDialect get defaultDialect => getDialect(_defaultDialectName);

  @override
  IGherkinDialect getDialect(
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

  @override
  List<String> get languages => _dialects.keys.toList();
}

/// Loads the bundled `assets/gherkin-languages.json` resource into a map of
/// dialects keyed by language tag.
///
/// Throws an [Exception] if the resource cannot be found.
Map<String, GherkinLanguageKeywords> loadGherkinLanguagesFromJsonAsset() {
  const dialectsAsset = 'gherkin-languages.json';
  const assetPath = 'assets/$dialectsAsset';
  final path = join(Directory.current.path, assetPath);
  final file = File(path);
  if (!file.existsSync()) {
    throw Exception('Gherkin language resource not found: $dialectsAsset');
  }
  final languagesJson = file.readAsStringSync();
  return _parseLanguages(languagesJson);
}

Map<String, GherkinLanguageKeywords> _parseLanguages(String languagesString) {
  final map = json.decode(languagesString) as Map<String, dynamic>;
  final languages = <String, GherkinLanguageKeywords>{};
  for (final entry in map.entries) {
    languages[entry.key] = GherkinLanguageKeywords.fromJson(
      entry.value as Map<String, dynamic>,
    );
  }
  return languages;
}
