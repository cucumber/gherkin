part of 'exceptions.dart';

/// An error raised while parsing a Gherkin document.
///
/// This type is `sealed`: its subtypes are a closed set defined by this
/// library, so callers can `switch` over them exhaustively and cannot add
/// their own subtypes. Use [ParserException.create] to build a plain,
/// location-carrying parser error that does not fit one of the more specific
/// subtypes.
sealed class ParserException implements Exception {
  /// Creates a location-less exception whose [message] is stored verbatim.
  ///
  /// Used by [CompositeParserException], whose message aggregates the
  /// already-formatted child messages and so needs no position prefix of its
  /// own.
  ParserException(this.message) : location = Location.empty;

  /// Creates an exception at [location], prefixing [message] with the
  /// canonical `(line:column): ` position marker (or `(-1,0): ` when the
  /// location is unknown).
  ///
  /// Folding the prefix into [message] makes the position part of the error
  /// message itself.
  ParserException.located(String message, this.location)
    : message = _formatMessage(message, location);

  /// Creates a plain located [ParserException] with a [message] and optional
  /// [location].
  ///
  /// Because [ParserException] is `sealed` it cannot be instantiated directly;
  /// this factory yields a private generic subtype for parser errors that do
  /// not correspond to one of the more specific subtypes (such as
  /// [UnexpectedTokenException] or [NoSuchLanguageException]).
  factory ParserException.create(String message, [Location location]) =
      _GenericParserException;

  /// A human-readable description of the error, including its
  /// `(line:column): ` position prefix when a [location] is known.
  final String message;

  /// The source location at which the error occurred, if known.
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

// The concrete [ParserException] returned by [ParserException.create].
//
// Kept private so the public error hierarchy stays a closed set of named
// subtypes; callers only ever observe it as a [ParserException].
final class _GenericParserException extends ParserException {
  _GenericParserException(super.message, [super.location = Location.empty])
    : super.located();
}
