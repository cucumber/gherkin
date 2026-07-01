import 'package:gherkin/src/language/location.dart';

/// An error raised while parsing a Gherkin document.
class ParserException implements Exception {
  /// Creates an exception with a [message] and an optional source [location].
  ParserException(this.message, [this.location = Location.empty]);

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
