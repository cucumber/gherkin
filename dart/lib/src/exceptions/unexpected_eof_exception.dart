part of 'exceptions.dart';

/// Exception thrown when the source ends before a required token.
final class UnexpectedEofException extends TokenParserException {
  /// Creates an exception for an unexpected end of file.
  ///
  /// [receivedToken] is the end-of-file token. [expectedTokenTypes] names the
  /// tokens that would have been valid.
  UnexpectedEofException(Token receivedToken, List<String> expectedTokenTypes)
    : super(_getMessage(expectedTokenTypes), receivedToken);

  static String _getMessage(List<String> expectedTokenTypes) =>
      'unexpected end of file, expected: ${expectedTokenTypes.join(", ")}';
}
