part of 'exceptions.dart';

/// Raised when a requested dialect (`# language:`) is not supported.
///
/// This is a [ParserException] subtype so that an unsupported dialect is
/// reported to callers as a `parseError` envelope rather than escaping as an
/// unhandled exception, matching the other first-party implementations.
final class NoSuchLanguageException extends ParserException {
  /// Creates an exception for the unsupported [language] at [location].
  NoSuchLanguageException(this.language, [Location location = Location.empty])
    : super.located('Language not supported: $language', location);

  /// The dialect name that was requested but is not supported.
  final String language;
}
