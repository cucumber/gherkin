part of 'exceptions.dart';

/// Raised when a requested dialect (`# language:`) is not supported.
///
/// Subtype of [ParserException] so `generateMessages` can report it as a
/// `parseError` envelope rather than letting it escape unhandled.
final class NoSuchLanguageException extends ParserException {
  /// Creates an exception for the unsupported [language] at [location].
  NoSuchLanguageException(String language, [Location location = Location.empty])
    : super.located('Language not supported: $language', location);
}
