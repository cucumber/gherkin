part of 'exceptions.dart';

/// An error raised while parsing a Gherkin document.
///
/// This type is `sealed`: its subtypes are a closed set defined by this
/// library, so callers can `switch` over them exhaustively and cannot add
/// their own subtypes. Use [ParserException.create] to build a plain,
/// location-carrying parser error that does not fit one of the more specific
/// subtypes.
sealed class ParserException implements Exception {
  /// Creates an exception with a [message] and an optional source [location].
  ParserException(this.message, [this.location = Location.empty]);

  /// Creates a plain [ParserException] with a [message] and optional
  /// [location].
  ///
  /// Because [ParserException] is `sealed` it cannot be instantiated directly;
  /// this factory yields a private generic subtype for parser errors that do
  /// not correspond to one of the more specific subtypes (such as
  /// [UnexpectedTokenException] or [NoSuchLanguageException]).
  factory ParserException.create(String message, [Location location]) =
      _GenericParserException;

  /// A human-readable description of the error.
  final String message;

  /// The source location at which the error occurred, if known.
  final Location location;

  @override
  String toString() {
    if (location.isEmpty) {
      return message;
    }
    return '(${location.line}:${location.column}): $message';
  }
}

/// The concrete [ParserException] returned by [ParserException.create].
///
/// Kept private so the public error hierarchy stays a closed set of named
/// subtypes; callers only ever observe it as a [ParserException].
final class _GenericParserException extends ParserException {
  _GenericParserException(super.message, [super.location = Location.empty]);
}
