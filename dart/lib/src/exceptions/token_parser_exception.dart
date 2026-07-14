part of 'exceptions.dart';

sealed class TokenParserException extends ParserException {
  TokenParserException(String message, Token receivedToken)
    : super.located(message, _getLocation(receivedToken));

  static Location _getLocation(Token receivedToken) {
    return receivedToken.isEof || receivedToken.location.column > 1
        ? receivedToken.location
        : Location(receivedToken.location.line, receivedToken.line.indent + 1);
  }
}
