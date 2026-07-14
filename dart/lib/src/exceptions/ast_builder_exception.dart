part of 'exceptions.dart';

final class AstBuilderException extends ParserException {
  AstBuilderException(super.message, super.location) : super.located();
}
