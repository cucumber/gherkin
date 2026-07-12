part of 'exceptions.dart';

/// A [ParserException] whose [Location] is derived from the offending [Token].
///
/// Sealed: subtypes are [UnexpectedTokenException] and
/// [UnexpectedEofException].
sealed class TokenParserException extends ParserException {
  /// Creates an exception with [message], locating it from [receivedToken].
  TokenParserException(String message, Token receivedToken)
    : super.located(message, _getLocation(receivedToken));

  static Location _getLocation(Token receivedToken) {
    return receivedToken.isEof || receivedToken.location.column > 1
        ? receivedToken.location
        : Location(receivedToken.location.line, receivedToken.line.indent + 1);
  }
}
