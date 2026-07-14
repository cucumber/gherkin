part of 'exceptions.dart';

final class UnexpectedEofException extends TokenParserException {
  UnexpectedEofException(Token receivedToken, List<String> expectedTokenTypes)
    : super(_getMessage(expectedTokenTypes), receivedToken);

  static String _getMessage(List<String> expectedTokenTypes) =>
      'unexpected end of file, expected: ${expectedTokenTypes.join(", ")}';
}
