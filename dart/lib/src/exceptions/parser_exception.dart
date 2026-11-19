part of 'exceptions.dart';

/// A failure reported while parsing Gherkin source.
sealed class ParserException implements Exception {
  /// Creates an exception with [message] and no source location.
  ParserException(this.message) : location = _emptyLocation;

  /// Creates an exception with [message] at [location].
  ///
  /// The stored [message] is prefixed with the line and column.
  ParserException.located(String message, this.location)
    : message = _formatMessage(message, location);

  /// Creates a parser exception with [message] at [location].
  ///
  /// When [location] is omitted, the exception has no source position.
  factory ParserException.create(String message, [messages.Location location]) =
      _GenericParserException;

  /// The error text, including a location prefix when one was provided.
  final String message;

  /// The source position of this failure.
  ///
  /// A line of `-1` means the failure has no source position.
  final messages.Location location;

  static String _formatMessage(String message, messages.Location location) {
    if (location == _emptyLocation) {
      return '(-1,0): $message';
    }
    return '(${location.line}:${location.column ?? 0}): $message';
  }

  @override
  String toString() => message;

  static const _emptyLocation = messages.Location(line: -1, column: 0);
}

final class _GenericParserException extends ParserException {
  _GenericParserException(
    super.message, [
    super.location = ParserException._emptyLocation,
  ]) : super.located();
}
