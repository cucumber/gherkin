part of 'exceptions.dart';

/// An error raised while parsing a Gherkin document.
///
/// Sealed: exhaustively `switch` over the library-defined subtypes.
/// Use [ParserException.create] for errors without a dedicated subtype.
sealed class ParserException implements Exception {
  /// Creates an exception whose [message] is stored without a location prefix.
  ///
  /// Used by [CompositeParserException] to aggregate already-located child
  /// messages.
  ParserException(this.message) : location = Location.empty;

  /// Creates an exception at [location], prefixing [message] with
  /// `(line:column): ` (or `(-1,0): ` when [location] is [Location.empty]).
  ParserException.located(String message, this.location)
    : message = _formatMessage(message, location);

  /// Creates a [ParserException] for errors without a dedicated subtype.
  ///
  /// When [location] is omitted, [Location.empty] is used.
  factory ParserException.create(String message, [Location location]) =
      _GenericParserException;

  /// The error message, including a `(line:column): ` prefix for located
  /// errors.
  final String message;

  /// The source [Location], or [Location.empty] when unknown.
  final Location location;

  static String _formatMessage(String message, Location location) {
    if (location.isEmpty) {
      return '(-1,0): $message';
    }
    return '(${location.line}:${location.column}): $message';
  }

  @override
  String toString() => message;
}

// Private fallback subtype for [ParserException.create].
final class _GenericParserException extends ParserException {
  _GenericParserException(super.message, [super.location = Location.empty])
    : super.located();
}
