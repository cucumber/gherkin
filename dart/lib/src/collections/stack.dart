/// A simple last-in, first-out (LIFO) stack of elements of type [T].
class Stack<T> {
  final List<T> _list = <T>[];

  /// Whether the stack has no elements.
  bool get isEmpty => _list.isEmpty;

  /// Whether the stack has at least one element.
  bool get isNotEmpty => _list.isNotEmpty;

  /// Pushes [value] onto the top of the stack.
  ///
  /// The top of the stack is kept at the end of the backing list so that
  /// [push], [pop], and [top] are all amortized O(1).
  void push(T value) => _list.add(value);

  /// Removes and returns the element at the top of the stack.
  ///
  /// Throws a [StateError] if the stack is empty.
  T pop() => _list.removeLast();

  /// Returns the element at the top of the stack without removing it.
  ///
  /// Throws a [StateError] if the stack is empty.
  T get top => _list.last;

  /// Removes all elements from the stack.
  void clear() => _list.clear();
}
