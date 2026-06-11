/// A value that can report whether it is a valid instance or an "empty"
/// sentinel, providing a null-object alternative to nullable references.
abstract class INullSafetyObject {
  /// Returns if this instance is invalid or not.
  bool get isEmpty;

  /// Returns if this instance is valid or not.
  bool get isNotEmpty => !isEmpty;
}
