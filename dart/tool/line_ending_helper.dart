import 'package:cucumber_gherkin/src/extensions/strings.dart';

/// Helpers for normalizing line endings so output is stable across platforms.
///
/// This is a development-only utility used by the token-dump tooling (`tool/`)
/// and the test suite; it is not part of the runtime library, so it lives under
/// `tool/` and is excluded from the published package.
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
