/// The base exception type for errors raised by this library.
class GherkinException implements Exception {
  /// Creates an exception with a [message] describing the [cause].
  GherkinException(this.message, this.cause);

  /// A human-readable description of the error.
  final String message;

  /// The underlying exception that triggered this error.
  final Exception cause;

  @override
  String toString() {
    return '$message: $cause';
  }
}
