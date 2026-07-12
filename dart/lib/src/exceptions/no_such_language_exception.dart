part of 'exceptions.dart';

/// Raised when a `# language:` dialect tag is not supported.
final class NoSuchLanguageException extends ParserException {
  /// Creates an exception for the unsupported [language] at [location].
  NoSuchLanguageException(String language, [Location location = Location.empty])
    : super.located('Language not supported: $language', location);
}
