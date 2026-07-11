/// Utility string operations used by the Gherkin scanners.
extension StringExtensions on String {
  // Leading/trailing horizontal-whitespace patterns.
  static final RegExp _leadingHorizontalWhitespace = RegExp(
    r'^[ \t\x0B\f\r\x85\xA0]+',
  );
  static final RegExp _trailingHorizontalWhitespace = RegExp(
    r'[ \t\x0B\f\r\x85\xA0]+$',
  );
  static final RegExp _trailingWhitespace = RegExp(
    r'[ \t\n\x0B\f\r\x85\xA0]+$',
  );

  /// Whether the string is empty or whitespace-only.
  bool get isEmptyOrWhiteSpace => trim().isEmpty;

  /// Removes leading horizontal whitespace while preserving line breaks.
  String ltrimKeepNewLines() => replaceAll(_leadingHorizontalWhitespace, '');

  /// Removes trailing horizontal whitespace while preserving line breaks.
  String rtrimKeepNewLines() => replaceAll(_trailingHorizontalWhitespace, '');

  /// Removes all trailing whitespace, including line breaks.
  String rtrim() => replaceAll(_trailingWhitespace, '');
}
