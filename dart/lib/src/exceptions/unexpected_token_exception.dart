part of 'exceptions.dart';

final class UnexpectedTokenException extends TokenParserException {
  UnexpectedTokenException(Token receivedToken, List<String> expectedTokenTypes)
    : super(_getMessage(receivedToken, expectedTokenTypes), receivedToken);

  static String _getMessage(
    Token receivedToken,
    List<String> expectedTokenTypes,
  ) =>
      "expected: ${expectedTokenTypes.join(", ")}, "
      "got '${receivedToken.tokenValue.trim()}'";
}
