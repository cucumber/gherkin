import 'package:gherkin/extensions.dart';

/// A one-based position (line and column) within a source document.
class Location {
  /// Creates a location at the given [line] and [column].
  const Location(this.line, this.column);

  /// A location representing an unknown/absent position.
  static const empty = Location(Int.min, Int.min);

  /// The one-based line number.
  final int line;

  /// The one-based column number.
  final int column;

  /// Whether this is the unknown/absent [empty] location.
  bool get isEmpty => line == empty.line && column == empty.column;
}
