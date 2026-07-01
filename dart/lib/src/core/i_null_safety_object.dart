/// A value that can report whether it is a valid instance or an "empty"
/// sentinel, providing a null-object alternative to nullable references.
///
/// Implementers only need to provide [isEmpty]; [isNotEmpty] is derived from
/// it. Use `with INullSafetyObject` to inherit that default, or
/// `implements INullSafetyObject` when only the interface is needed.
mixin INullSafetyObject {
  /// Whether this instance is the empty/invalid sentinel.
  bool get isEmpty;

  /// Whether this instance is a valid (non-empty) value.
  bool get isNotEmpty => !isEmpty;
}
