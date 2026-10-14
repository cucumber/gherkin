part of 'exceptions.dart';

/// Exception thrown when a requested dialect is not available.
final class NoSuchLanguageException extends ParserException {
  /// Creates an exception for the unsupported [language].
  ///
  /// [location] identifies the language header when the dialect was requested
  /// from source. When omitted, the exception has no source position.
  NoSuchLanguageException(
    String language, [
    messages.Location location = ParserException._emptyLocation,
  ]) : super.located('Language not supported: $language', location);
}
