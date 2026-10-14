part of 'exceptions.dart';

/// A [ParserException] whose location comes from a received [Token].
sealed class TokenParserException extends ParserException {
  /// Creates an exception with [message] at the location of [receivedToken].
  TokenParserException(String message, Token receivedToken)
    : super.located(message, _getLocation(receivedToken));

  static messages.Location _getLocation(Token receivedToken) {
    return receivedToken.isEof || receivedToken.location.column != null
        ? receivedToken.location
        : messages.Location(
            line: receivedToken.location.line,
            column: receivedToken.line!.indent + 1,
          );
  }
}
