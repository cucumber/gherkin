/// A position within a source document.
///
/// Line numbers are one-based. Column numbers are one-based after matching;
/// column `0` may appear on freshly scanned tokens before matching.
class Location {
  /// Creates a location at the given [line] and [column].
  const Location(this.line, this.column);

  // Sentinel for an unset line or column. Real positions are 1-based, so a
  // negative value never collides with a legitimate one.
  static const int _unset = -1;

  /// A location representing an unknown/absent position.
  static const empty = Location(_unset, _unset);

  /// The one-based line number.
  final int line;

  /// The column number (one-based after matching; `0` before matching).
  final int column;

  /// Whether this is the unknown/absent [empty] location.
  bool get isEmpty => line == empty.line && column == empty.column;

  /// Whether [column] is not the [empty] sentinel (`-1`).
  ///
  /// Column `0` (pre-match placeholder) still returns `true`.
  bool get hasColumn => column != _unset;
}
