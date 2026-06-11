import 'package:gherkin/src/exceptions/parser_exception.dart';

/// Aggregates several [ParserException]s collected during a single parse.
class CompositeParserException extends ParserException {
  /// Creates an exception wrapping all of the given [errors].
  CompositeParserException(this.errors) : super(_getMessage(errors));

  /// The individual errors encountered during parsing.
  final List<ParserException> errors;

  static String _getMessage(List<ParserException> errors) {
    final linedErrors = errors.map((e) => e.message).join('\n');
    return 'Parser errors:\n$linedErrors';
  }
}
