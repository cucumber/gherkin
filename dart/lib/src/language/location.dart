/// A one-based position (line and column) within a source document.
class Location {
  /// Creates a location at the given [line] and [column].
  const Location(this.line, this.column);

  /// Marks an unset line or column.
  ///
  /// Real values are non-negative (lines and columns are 1-based), so a
  /// negative value never collides with a legitimate one. Uses a negative
  /// literal rather than `1 << 63`, which does not produce the 64-bit minimum
  /// integer on the web/JS target and would break the sentinel there.
  static const int _unset = -1;

  /// A location representing an unknown/absent position.
  static const empty = Location(_unset, _unset);

  /// The one-based line number.
  final int line;

  /// The one-based column number.
  final int column;

  /// Whether this is the unknown/absent [empty] location.
  bool get isEmpty => line == empty.line && column == empty.column;

  /// Whether the [column] is set (has a known position).
  bool get hasColumn => column != _unset;
}
