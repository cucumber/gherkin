part of 'exceptions.dart';

/// A [ParserException] whose location is derived from the offending token.
///
/// This type is `sealed`: its subtypes ([UnexpectedTokenException] and
/// [UnexpectedEofException]) are a closed set defined by this library.
sealed class TokenParserException extends ParserException {
  /// Creates an exception with [message], locating it at [receivedToken].
  TokenParserException(String message, Token receivedToken)
    : super.located(message, _getLocation(receivedToken));

  static Location _getLocation(Token receivedToken) {
    return receivedToken.isEof || receivedToken.location.column > 1
        ? receivedToken.location
        : Location(receivedToken.location.line, receivedToken.line.indent + 1);
  }
}
