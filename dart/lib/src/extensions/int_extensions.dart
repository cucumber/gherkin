/// Convenience queries for the [Int.min] sentinel value.
extension IntExtensions on int {
  /// Whether this value equals the [Int.min] sentinel.
  bool get isMin => this == Int.min;

  /// Whether this value differs from the [Int.min] sentinel.
  bool get isNotMin => !isMin;
}

/// Integer constants used as sentinels throughout the library.
class Int {
  /// An "unset" sentinel for line numbers, columns, and indents.
  ///
  /// All real values for these are non-negative (columns and lines are
  /// 1-based, indents are 0-based character offsets), so a negative value can
  /// never collide with a legitimate one. A negative literal is used rather
  /// than `1 << 63` because bit-shift arithmetic does not produce the 64-bit
  /// minimum integer on the web/JS target, which would silently break the
  /// sentinel there.
  static const int min = -1;
}
