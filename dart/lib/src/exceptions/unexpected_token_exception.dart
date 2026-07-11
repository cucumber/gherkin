part of 'exceptions.dart';

/// Raised when the parser encounters a token it did not expect.
final class UnexpectedTokenException extends TokenParserException {
  /// Creates an exception for an unexpected [receivedToken].
  ///
  /// [expectedTokenTypes] lists the token types the parser would have accepted.
  UnexpectedTokenException(Token receivedToken, List<String> expectedTokenTypes)
    : super(_getMessage(receivedToken, expectedTokenTypes), receivedToken);

  static String _getMessage(
    Token receivedToken,
    List<String> expectedTokenTypes,
  ) =>
      "expected: ${expectedTokenTypes.join(", ")}, "
      "got '${receivedToken.tokenValue.trim()}'";
}
