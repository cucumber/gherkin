/// A span of text on a line together with its one-based column position.
///
/// Used to represent tags and table cells recognized while scanning a line.
class GherkinLineSpan {
  /// Creates a span starting at [column] containing [text].
  const GherkinLineSpan(this.column, this.text);

  /// One-based line position.
  final int column;

  /// Text part of the line.
  final String text;
}
