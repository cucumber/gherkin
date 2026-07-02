part of 'exceptions.dart';

/// Aggregates several [ParserException]s collected during a single parse.
final class CompositeParserException extends ParserException {
  /// Creates an exception wrapping all of the given [errors].
  CompositeParserException(this.errors) : super(_getMessage(errors));

  /// The individual errors encountered during parsing.
  final List<ParserException> errors;

  static String _getMessage(List<ParserException> errors) {
    final linedErrors = errors.map((e) => e.message).join('\n');
    return 'Parser errors:\n$linedErrors';
  }

  /// Renders each aggregated error on its own line, including the location
  /// prefix of every error rather than just their bare messages.
  @override
  String toString() {
    final linedErrors = errors.map((e) => e.toString()).join('\n');
    return 'Parser errors:\n$linedErrors';
  }
}
