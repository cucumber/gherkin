part of 'exceptions.dart';

/// A [ParserException] that reports several parser failures together.
final class CompositeParserException extends ParserException {
  /// Creates an exception that wraps [errors].
  CompositeParserException(this.errors) : super(_getMessage(errors));

  /// The parser failures included in this exception.
  final List<ParserException> errors;

  static String _getMessage(List<ParserException> errors) {
    final linedErrors = errors.map((e) => e.message).join('\n');
    return 'Parser errors:\n$linedErrors';
  }
}
