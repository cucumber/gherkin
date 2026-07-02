import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:cucumber_gherkin/src/language/gherkin_language_keywords.dart';

/// Returns the bundled Gherkin dialects, keyed by language tag.
///
/// The dialects are embedded as generated Dart source in
/// `dialects_builtin.g.dart` (produced from `gherkin-languages.json` by the
/// `dialects_builtin.g.dart.jq` script), so loading does not depend on the
/// current working directory, runtime asset resolution, or the package layout.
Map<String, GherkinLanguageKeywords> loadGherkinLanguagesFromJsonAsset() {
  return builtinDialects;
}
