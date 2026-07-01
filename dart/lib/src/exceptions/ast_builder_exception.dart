import 'package:cucumber_gherkin/src/exceptions/parser_exception.dart';

/// Raised by the AST builder when the token stream is structurally invalid
/// (for example, a data table with an inconsistent cell count).
class AstBuilderException extends ParserException {
  /// Creates an exception with [message] at the given [location].
  AstBuilderException(super.message, super.location);
}
