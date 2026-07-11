part of 'exceptions.dart';

/// Raised when a requested dialect (`# language:`) is not supported.
///
/// This is a [ParserException] subtype so that an unsupported dialect is
/// reported to callers as a `parseError` envelope rather than escaping as an
/// unhandled exception.
final class NoSuchLanguageException extends ParserException {
  /// Creates an exception for the unsupported [language] at [location].
  NoSuchLanguageException(String language, [Location location = Location.empty])
    : super.located('Language not supported: $language', location);
}
