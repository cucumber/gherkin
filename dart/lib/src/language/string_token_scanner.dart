import 'package:cucumber_gherkin/src/language/gherkin_line.dart';
import 'package:cucumber_gherkin/src/language/location.dart';
import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/token_scanner.dart';

class StringTokenScanner implements TokenScanner {
  StringTokenScanner(String source) : _linesIterator = _splitLines(source);

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

  @override
  Token read() {
    final location = Location(++_lineNumber, 0);
    if (_linesIterator.moveNext()) {
      return Token(GherkinLine(_linesIterator.current, _lineNumber), location);
    }
    return Token(GherkinLine.eof(), location);
  }
}
