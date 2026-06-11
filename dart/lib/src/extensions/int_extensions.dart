/// Convenience queries for the [Int.min] sentinel value.
extension IntExtensions on int {
  /// Whether this value equals the [Int.min] sentinel.
  bool get isMin => this == Int.min;

  /// Whether this value differs from the [Int.min] sentinel.
  bool get isNotMin => !isMin;
}

/// Integer constants used as sentinels throughout the library.
class Int {
  /// The smallest 64-bit signed integer, used as an "unset" sentinel.
  static const int min = 1 << 63;
}
