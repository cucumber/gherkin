import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:cucumber_gherkin/src/parser/token.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// Reads [Token] values from a Gherkin source string, one per line.
class TokenScanner {
  /// Creates a scanner that yields one token per line of [source].
  ///
  /// A trailing newline does not produce an extra empty line. An empty
  /// [source] yields only an end-of-file token.
  TokenScanner(String source) : _linesIterator = _splitLines(source);

  static Iterator<String> _splitLines(String source) {
    if (source.isEmpty) {
      return const <String>[].iterator;
    }
    final lines = source.split(_lineSeparator);
    if (lines.length > 1 && lines.last.isEmpty) {
      lines.removeLast();
    }
    return lines.iterator;
  }

  static final RegExp _lineSeparator = RegExp(r'\r?\n');

  final Iterator<String> _linesIterator;
  int _lineNumber = 0;

  /// The next token, including the end-of-file token after the last line.
  Token read() {
    final location = messages.Location(line: ++_lineNumber);
    if (_linesIterator.moveNext()) {
      return Token(GherkinLine(_linesIterator.current, _lineNumber), location);
    }
    return Token.eof(location);
  }
}
