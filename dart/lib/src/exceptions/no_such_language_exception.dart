part of 'exceptions.dart';

/// Raised when a language tag is not in the dialect map.
///
/// Triggered by an unsupported `# language:` header or an invalid default
/// dialect supplied to the token matcher.
final class NoSuchLanguageException extends ParserException {
  /// Creates an exception for the unsupported [language] at [location].
  NoSuchLanguageException(String language, [Location location = Location.empty])
    : super.located('Language not supported: $language', location);
}
