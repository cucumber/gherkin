/// Utility string operations used by the Gherkin scanners.
extension StringExtensions on String {
  // Leading/trailing horizontal-whitespace patterns. Compiled once and reused
  // rather than rebuilt per call (these run per table cell). \xA0 is a
  // non-breaking space, which some trims miss:
  // https://stackoverflow.com/questions/1060570/why-is-non-breaking-space-not-a-whitespace-character-in-java
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

  /// Splits the string at matches of [pattern] and returns a list of
  /// substrings.
  ///
  /// The [limit] controls how many substrings are produced:
  ///
  /// * `limit == 0` (the default) splits at every match, like [String.split].
  /// * `limit > 0` produces at most [limit] substrings: the string is split at
  ///   the first `limit - 1` matches and the unsplit remainder (which may still
  ///   contain further matches of [pattern]) becomes the final substring.
  ///
  /// Walks the actual match offsets, so it is correct for multi-character and
  /// regular-expression separators and for strings where an earlier substring
  /// repeats later.
  ///
  /// Throws an [ArgumentError] if [limit] is negative.
  List<String> splitWithLimit(Pattern pattern, {int limit = 0}) {
    if (limit < 0) {
      throw ArgumentError.value(limit, 'limit', 'must not be negative');
    }
    if (limit == 0) {
      return split(pattern);
    }
    if (limit == 1) {
      return [this];
    }

    final result = <String>[];
    var start = 0;
    for (final match in pattern.allMatches(this)) {
      // A zero-width match at the current cursor cannot make progress; skip it
      // so we don't emit spurious empty substrings (mirrors [String.split]).
      if (match.end == start && match.start == match.end) {
        continue;
      }
      result.add(substring(start, match.start));
      start = match.end;
      // One slot must remain for the unsplit remainder.
      if (result.length == limit - 1) {
        break;
      }
    }
    result.add(substring(start));
    return result;
  }

  /// Removes leading horizontal whitespace while preserving line breaks.
  String ltrimKeepNewLines() => replaceAll(_leadingHorizontalWhitespace, '');

  /// Removes trailing horizontal whitespace while preserving line breaks.
  String rtrimKeepNewLines() => replaceAll(_trailingHorizontalWhitespace, '');

  /// Removes all trailing whitespace, including line breaks.
  String rtrim() => replaceAll(_trailingWhitespace, '');
}
