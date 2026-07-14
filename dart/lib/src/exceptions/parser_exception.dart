part of 'exceptions.dart';

sealed class ParserException implements Exception {
  ParserException(this.message) : location = Location.empty;

  ParserException.located(String message, this.location)
    : message = _formatMessage(message, location);

  factory ParserException.create(String message, [Location location]) =
      _GenericParserException;

  final String message;

  final Location location;

  static String _formatMessage(String message, Location location) {
    if (location.isEmpty) {
      return '(-1,0): $message';
    }
    return '(${location.line}:${location.column}): $message';
  }

  @override
  String toString() => message;
}

final class _GenericParserException extends ParserException {
  _GenericParserException(super.message, [super.location = Location.empty])
    : super.located();
}
