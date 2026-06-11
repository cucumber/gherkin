import 'package:gherkin/extensions.dart';

/// Helpers for normalizing line endings so output is stable across platforms.
class LineEndingHelper {
  /// Converts `\r\n` to `\n` and trims trailing newlines from [text].
  static String normalizeLineEndings(String text) {
    if (text.isEmpty) {
      return text;
    }
    return text.replaceAll('\r\n', '\n').trimEnd('\n');
  }

  /// Removes all carriage returns and line feeds from [text] and trims it.
  static String stripLineEndings(String text) {
    return text.replaceAll('\r', '').replaceAll('\n', '').trim();
  }
}
