import 'package:gherkin/src/language/i_gherkin_dialect.dart';
import 'package:gherkin/src/language/location.dart';

/// Supplies [IGherkinDialect]s by language tag.
abstract class IGherkinDialectProvider {
  /// The dialect used when none is specified.
  IGherkinDialect get defaultDialect;

  /// Returns the dialect for [language].
  ///
  /// [location] is used to report a `NoSuchLanguageException` when the language
  /// is not supported.
  IGherkinDialect getDialect(String language, Location location);

  /// The language tags of all supported dialects.
  List<String> get languages;
}
