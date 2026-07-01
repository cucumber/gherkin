import 'package:gherkin/src/exceptions/token_parser_exception.dart';
import 'package:gherkin/src/language/token.dart';

/// Raised when the file ends while the parser still expected more tokens.
class UnexpectedEofException extends TokenParserException {
  /// Creates an exception for an unexpected end of file.
  ///
  /// [expectedTokenTypes] lists the token types the parser would have accepted.
  UnexpectedEofException(Token receivedToken, this.expectedTokenTypes)
    : super(_getMessage(expectedTokenTypes), receivedToken);

  /// The token types that would have been accepted instead.
  final List<String> expectedTokenTypes;

  static String _getMessage(List<String> expectedTokenTypes) =>
      'unexpected end of file, expected: ${expectedTokenTypes.join(", ")}';
}
