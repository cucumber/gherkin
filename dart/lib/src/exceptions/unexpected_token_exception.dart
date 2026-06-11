import 'package:gherkin/language.dart';

import 'package:gherkin/src/exceptions/token_parser_exception.dart';

/// Raised when the parser encounters a token it did not expect.
class UnexpectedTokenException extends TokenParserException {
  /// Creates an exception for an unexpected [receivedToken].
  ///
  /// [expectedTokenTypes] lists the token types the parser would have accepted.
  UnexpectedTokenException(this.receivedToken, this.expectedTokenTypes)
    : super(_getMessage(receivedToken, expectedTokenTypes), receivedToken);

  /// The token that was actually received.
  final Token receivedToken;

  /// The token types that would have been accepted instead.
  final List<String> expectedTokenTypes;

  static String _getMessage(
    Token receivedToken,
    List<String> expectedTokenTypes,
  ) =>
      "expected: ${expectedTokenTypes.join(", ")}, "
      "got '${receivedToken.tokenValue.trim()}'";
}
