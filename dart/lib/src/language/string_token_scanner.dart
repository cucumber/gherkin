import 'dart:convert';

import 'package:gherkin/language.dart';
import 'package:gherkin/parser.dart';

/// An [ITokenScanner] that reads a Gherkin document from an in-memory string.
class StringTokenScanner implements ITokenScanner {
  /// Creates a scanner over the lines of [source].
  StringTokenScanner(String source)
    : _linesIterator = LineSplitter.split(source).iterator;

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
