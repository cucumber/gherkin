import 'package:meta/meta.dart';

/// A span of text on a line together with its one-based column position.
///
/// Used to represent tags and table cells recognized while scanning a line.
@immutable
class GherkinLineSpan {
  /// Creates a span starting at [column] containing [text].
  const GherkinLineSpan(this.column, this.text);

  /// One-based line position
  final int column;

  /// Text part of the line
  final String text;

  @override
  bool operator ==(Object other) =>
      identical(this, other) ||
      (other is GherkinLineSpan &&
          column == other.column &&
          text == other.text);

  @override
  int get hashCode => 31 * column + text.hashCode;
}
