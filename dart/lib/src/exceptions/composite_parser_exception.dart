part of 'exceptions.dart';

final class CompositeParserException extends ParserException {
  CompositeParserException(this.errors) : super(_getMessage(errors));

  final List<ParserException> errors;

  static String _getMessage(List<ParserException> errors) {
    final linedErrors = errors.map((e) => e.message).join('\n');
    return 'Parser errors:\n$linedErrors';
  }
}
