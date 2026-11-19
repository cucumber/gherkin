part of 'exceptions.dart';

/// Exception thrown when the AST builder rejects a parsed construct.
final class AstBuilderException extends ParserException {
  /// Creates an exception with [message] at [location].
  AstBuilderException(super.message, super.location) : super.located();
}
