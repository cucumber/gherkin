part of 'exceptions.dart';

/// Raised when the input ends while the parser still expected more tokens.
final class UnexpectedEofException extends TokenParserException {
  /// Creates an exception for an unexpected end of file.
  ///
  /// [receivedToken] is the EOF token used to determine error [location].
  /// [expectedTokenTypes] lists the token types the parser would have accepted.
  UnexpectedEofException(Token receivedToken, List<String> expectedTokenTypes)
    : super(_getMessage(expectedTokenTypes), receivedToken);

  static String _getMessage(List<String> expectedTokenTypes) =>
      'unexpected end of file, expected: ${expectedTokenTypes.join(", ")}';
}
