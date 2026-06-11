/// String constants used throughout the library.
class Strings {
  /// The empty string.
  static const empty = '';
}

/// Utility string operations used by the Gherkin scanners.
extension StringExtensions on String {
  /// Indicates whether a specified string is `empty` or consists only
  /// of `white-space` characters.
  bool get isEmptyOrWhiteSpace => trim().isEmpty;

  /// Splits the string at matches of [pattern] and returns a list of
  /// substrings.
  ///
  /// The [limit] parameter is used to decide how many times is to split
  /// the string.
  List<String> splitWithLimit(Pattern pattern, {int limit = 0}) {
    if (limit == 0) {
      return split(pattern);
    }
    final result = <String>[];
    // Positive.
    if (limit > 0) {
      final parts = split(pattern);
      if (parts.isNotEmpty) {
        final maxParts = limit - 1;
        var index = 0;
        while (index < maxParts && index < parts.length) {
          result.add(parts[index]);
          index++;
        }
        if (result.isEmpty) {
          result.add(this);
        } else if (index < parts.length) {
          final lastPart = result[result.length - 1];
          final start = indexOf(lastPart);
          final complement = substring(start + lastPart.length + 1);
          result.add(complement);
        }
      } else {
        result.add(this);
      }
    } else {
      throw UnimplementedError('splitWithLimit do not supports negative limit');
    }
    return result;
  }

  /// Removes leading horizontal whitespace while preserving line breaks.
  String ltrimKeepNewLines() {
    // https://stackoverflow.com/questions/1060570/why-is-non-breaking-space-not-a-whitespace-character-in-java
    final regexp = RegExp(r'^[ \t\x0B\f\r\x85\xA0]+');
    return replaceAll(regexp, '');
  }

  /// Removes trailing horizontal whitespace while preserving line breaks.
  String rtrimKeepNewLines() {
    // https://stackoverflow.com/questions/1060570/why-is-non-breaking-space-not-a-whitespace-character-in-java
    final regexp = RegExp(r'[ \t\x0B\f\r\x85\xA0]+$');
    return replaceAll(regexp, '');
  }

  /// Removes all trailing whitespace, including line breaks.
  String rtrim() {
    final regexp = RegExp(r'[ \t\n\x0B\f\r\x85\xA0]+$');
    return replaceAll(regexp, '');
  }

  /// Removes all trailing occurrences of a character specified in an string.
  /// The default value of [trimChar] is an white-space.
  String trimEnd([String trimChar = ' ']) {
    if (trimChar.length > 1 || trimChar.isEmpty) {
      throw ArgumentError('trimChar must be one char and cannot be empty');
    }
    var index = length - 1;
    for (; index > 0; index--) {
      if (this[index] != trimChar) {
        break;
      }
    }
    return substring(0, index + 1);
  }
}
