part of 'exceptions.dart';

sealed class ParserException implements Exception {
  ParserException(this.message) : location = _emptyLocation;

  ParserException.located(String message, this.location)
    : message = _formatMessage(message, location);

  factory ParserException.create(String message, [messages.Location location]) =
      _GenericParserException;

  final String message;

  final messages.Location location;

  static String _formatMessage(String message, messages.Location location) {
    if (location == _emptyLocation) {
      return '(-1,0): $message';
    }
    return '(${location.line}:${location.column}): $message';
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
