part of 'exceptions.dart';

/// Raised when a requested dialect (`# language:`) is not supported.
///
/// Subtype of [ParserException] for unsupported `# language:` dialect tags.
final class NoSuchLanguageException extends ParserException {
  /// Creates an exception for the unsupported [language] at [location].
  NoSuchLanguageException(String language, [Location location = Location.empty])
    : super.located('Language not supported: $language', location);
}
