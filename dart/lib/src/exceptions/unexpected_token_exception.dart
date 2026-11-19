part of 'exceptions.dart';

/// Exception thrown when the parser receives a token it cannot accept.
final class UnexpectedTokenException extends TokenParserException {
  /// Creates an exception for [receivedToken].
  ///
  /// [expectedTokenTypes] names the tokens that would have been valid.
  UnexpectedTokenException(Token receivedToken, List<String> expectedTokenTypes)
    : super(_getMessage(receivedToken, expectedTokenTypes), receivedToken);

  static String _getMessage(
    Token receivedToken,
    List<String> expectedTokenTypes,
  ) =>
      "expected: ${expectedTokenTypes.join(", ")}, "
      "got '${receivedToken.tokenValue.trim()}'";
}
