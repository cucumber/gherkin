part of 'exceptions.dart';

sealed class TokenParserException extends ParserException {
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
