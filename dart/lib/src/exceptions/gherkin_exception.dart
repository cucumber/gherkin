/// The base exception type for errors raised by this library.
///
/// This represents a fatal, non-parse error (such as a missing bundled
/// resource or an I/O failure). Malformed Gherkin input is *not* reported this
/// way; it is emitted as a `parseError` envelope instead.
class GherkinException implements Exception {
  /// Creates an exception with a [message] optionally describing the [cause].
  GherkinException(this.message, [this.cause]);

  /// A human-readable description of the error.
  final String message;

  /// The underlying exception that triggered this error, if any.
  final Exception? cause;

  @override
  String toString() {
    if (cause == null) {
      return message;
    }
    return '$message: $cause';
  }
}
