/// A simple last-in, first-out (LIFO) stack of elements of type [T].
class Stack<T> {
  final List<T> _list = <T>[];

  /// Check if the stack is empty.
  bool get isEmpty => _list.isEmpty;

  /// Check if the stack is not empty.
  bool get isNotEmpty => _list.isNotEmpty;

  /// Push element in top of the stack.
  void push(T value) => _list.insert(0, value);

  /// Get the top of the stack and delete it.
  T pop() => _list.removeAt(0);

  /// Get the top of the stack without deleting it.
  T get top => _list.first;

  /// Removes all elements from the stack.
  void clear() => _list.clear();
}
