import 'package:cucumber_gherkin/src/language/gherkin_line.dart';
import 'package:cucumber_gherkin/src/language/location.dart';
import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/token_scanner.dart';

/// A [TokenScanner] that reads a Gherkin document from an in-memory string.
class StringTokenScanner implements TokenScanner {
  /// Creates a scanner over the lines of [source].
  ///
  /// Lines are separated on `\r?\n`. A lone `\r` is *not* a line separator and
  /// is kept as part of the line, so the string and file scanners agree.
  /// Dart's `LineSplitter`, by contrast, treats a bare `\r` as a break, so it
  /// is deliberately not used here.
  StringTokenScanner(String source) : _linesIterator = _splitLines(source);

  static Iterator<String> _splitLines(String source) {
    // An empty source has no content lines. `split` would otherwise yield a
    // single empty segment, producing a spurious blank line (and an `Empty`
    // token) for input that a file-based scanner reports as immediate EOF.
    if (source.isEmpty) {
      return const <String>[].iterator;
    }
    final lines = source.split(_lineSeparator);
    // A trailing separator produces a final empty segment; drop it so a file
    // ending in a newline does not yield a spurious blank line.
    if (lines.length > 1 && lines.last.isEmpty) {
      lines.removeLast();
    }
    return lines.iterator;
  }

  static final RegExp _lineSeparator = RegExp(r'\r?\n');

  final Iterator<String> _linesIterator;

  /// The number of lines read so far (the line of the most recent token).
  int lineNumber = 0;

  @override
  Token read() {
    final location = Location(++lineNumber, 0);
    if (_linesIterator.moveNext()) {
      return Token(GherkinLine(_linesIterator.current, lineNumber), location);
    }
    return Token(GherkinLine.eof(), location);
  }
}
