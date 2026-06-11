import 'package:gherkin/language.dart';

import 'package:gherkin/src/exceptions/parser_exception.dart';

/// Raised when a requested dialect (`# language:`) is not supported.
class NoSuchLanguageException extends ParserException {
  /// Creates an exception for the unsupported [language] at [location].
  NoSuchLanguageException(String language, [Location location = Location.empty])
    : super('Language not supported: $language', location) {
    if (language.isEmpty) {
      throw ArgumentError.notNull('language');
    }
  }
}
