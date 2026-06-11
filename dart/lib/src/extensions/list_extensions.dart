/// Convenience accessors for lists.
extension ListExtension<T> on List<T> {
  /// Returns the first element, or [defaultResult] if the list is empty.
  T singleOrDefault(T defaultResult) => isNotEmpty ? first : defaultResult;
}
