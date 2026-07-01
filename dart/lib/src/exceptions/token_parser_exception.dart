import 'package:cucumber_gherkin/src/exceptions/parser_exception.dart';
import 'package:cucumber_gherkin/src/language/location.dart';
import 'package:cucumber_gherkin/src/language/token.dart';

/// A [ParserException] whose location is derived from the offending token.
class TokenParserException extends ParserException {
  /// Creates an exception with [message], locating it at [receivedToken].
  TokenParserException(String message, Token receivedToken)
    : super(message, _getLocation(receivedToken));

  static Location _getLocation(Token receivedToken) {
    return receivedToken.isEof || receivedToken.location.column > 1
        ? receivedToken.location
        : Location(receivedToken.location.line, receivedToken.line.indent + 1);
  }
}
