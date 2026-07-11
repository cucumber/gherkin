import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/language/gherkin_language_constants.dart';
import 'package:cucumber_gherkin/src/language/location.dart';

/// A single source line, providing the queries the scanner needs to classify
/// it.
class GherkinLine {
  /// Creates a line from its [_lineText] at the one-based [_lineNumber].
  GherkinLine(this._lineText, this._lineNumber)
    : _trimmedLineText = _lineText.trimLeft(),
      _isEof = false;

  /// Creates the line that marks the end of the file.
  GherkinLine.eof()
    : _lineText = '',
      _lineNumber = _unsetLineNumber,
      _trimmedLineText = '',
      _isEof = true;

  /// Placeholder line number for the end-of-file marker, which has no position
  /// in the source. Real line numbers are 1-based, so a negative value can
  /// never collide with one.
  static const int _unsetLineNumber = -1;

  // Columns are 1-indexed.
  static const int _offset = 1;

  /// Matches the whitespace-preceded comment prefix that ends the tag portion
  /// of a line. Compiled once and reused across lines.
  static final RegExp _commentSuffix = RegExp(r'\s' + commentPrefix);

  /// Matches a token containing no whitespace. Compiled once and reused rather
  /// than rebuilt for every tag on every line.
  static final RegExp _nonWhitespaceToken = RegExp(r'^\S+$');

  // Horizontal-whitespace patterns used when trimming table cells / tags
  // without consuming newlines.
  static final RegExp _leadingHorizontalWhitespace = RegExp(
    r'^[ \t\x0B\f\r\x85\xA0]+',
  );
  static final RegExp _trailingHorizontalWhitespace = RegExp(
    r'[ \t\x0B\f\r\x85\xA0]+$',
  );
  static final RegExp _trailingWhitespace = RegExp(
    r'[ \t\n\x0B\f\r\x85\xA0]+$',
  );

  final String _lineText;
  final int _lineNumber;
  final String _trimmedLineText;
  final bool _isEof;

  /// Whether this line is the end-of-file marker.
  bool get isEof => _isEof;

  /// Called by the parser to indicate non-streamed reading (for example during
  /// look-ahead). No-op for this in-memory implementation.
  void detach() {}

  /// Returns the line text.
  ///
  /// [indentToRemove] is the maximum number of whitespace characters to remove
  /// from the start of the line; a negative value removes all leading
  /// whitespace.
  String getLineText([int indentToRemove = 0]) {
    if (indentToRemove < 0 || indentToRemove > indent) {
      return _trimmedLineText;
    }
    return _lineText.substring(indentToRemove);
  }

  /// Returns the remaining part of the line after the first [length]
  /// characters, trimmed.
  String getRestTrimmed(int length) =>
      _trimmedLineText.substring(length).trim();

  /// The number of whitespace characters at the beginning of the line.
  int get indent => _lineText.length - _trimmedLineText.length;

  /// Whether the line is empty or contains whitespace only.
  bool get isEmptyLine => _trimmedLineText.isEmpty;

  /// Whether the beginning of the line (ignoring leading whitespace) matches
  /// [prefix].
  bool startsWith(String prefix) => _trimmedLineText.startsWith(prefix);

  /// Whether the beginning of the line (ignoring leading whitespace) matches
  /// the title keyword [text] followed by a `:` separator.
  bool startsWithTitleKeyword(String text) =>
      startsWith('$text$titleKeywordSeparator');

  /// Parses the line as a tag list, returning a `(column, text)` span for each
  /// tag (including its leading `@`).
  Iterable<GherkinLineSpan> get tags {
    final tags = <GherkinLineSpan>[];
    final commentMatch = _commentSuffix.firstMatch(_trimmedLineText);
    final uncommentedLine =
        commentMatch == null
            ? _trimmedLineText
            : _trimmedLineText.substring(0, commentMatch.start);

    var indexInUncommentedLine = 0;
    final elements = uncommentedLine.split(tagPrefix);

    for (final element in elements) {
      final token = element.replaceAll(_trailingWhitespace, '');
      if (token.isEmpty) {
        continue;
      }
      final symbolLength =
          uncommentedLine.substring(0, indexInUncommentedLine).length;
      final column = indent + symbolLength + 1;
      if (!_nonWhitespaceToken.hasMatch(token)) {
        throw ParserException.create(
          'A tag may not contain whitespace',
          Location(_lineNumber, column),
        );
      }
      tags.add(GherkinLineSpan(column, tagPrefix + token));
      indexInUncommentedLine += element.length + 1;
    }

    return tags;
  }

  /// Parses the line as a table row, returning a `(column, text)` span for each
  /// trimmed cell value.
  Iterable<GherkinLineSpan> get tableCells {
    final lineSpans = <GherkinLineSpan>[];
    var cellBuffer = StringBuffer();
    var beforeFirst = true;
    var col = 0;
    var cellStart = 0;
    var escape = false;
    // Columns are counted in Unicode code points.
    for (final rune in _lineText.runes) {
      final chr = String.fromCharCode(rune);
      if (escape) {
        switch (chr) {
          case tableCellNewLineEscape:
            cellBuffer.write('\n');
          case tableCellEscapeChar:
            cellBuffer.write(r'\');
          case tableCellSeparator:
            cellBuffer.write('|');
          default:
            // Invalid escape; ignore it.
            cellBuffer.write(r'\');
            cellBuffer.write(chr);
        }
        escape = false;
      } else {
        switch (chr) {
          case tableCellEscapeChar:
            escape = true;
          case tableCellSeparator:
            if (beforeFirst) {
              // Skip the first empty span
              beforeFirst = false;
            } else {
              final cell = cellBuffer.toString();
              final leftTrimmedCell = cell.replaceAll(
                _leadingHorizontalWhitespace,
                '',
              );
              final cellIndent = cell.length - leftTrimmedCell.length;
              final column = cellStart + cellIndent + _offset;
              final text = leftTrimmedCell.replaceAll(
                _trailingHorizontalWhitespace,
                '',
              );
              lineSpans.add(GherkinLineSpan(column, text));
            }
            cellBuffer = StringBuffer();
            cellStart = col + 1;
          default:
            cellBuffer.write(chr);
        }
      }
      col++;
    }
    return lineSpans;
  }
}

/// A span of text on a line together with its one-based column position.
///
/// Used for tags and table cells recognized while scanning a line.
class GherkinLineSpan {
  /// Creates a span starting at [column] containing [text].
  const GherkinLineSpan(this.column, this.text);

  /// One-based line position.
  final int column;

  /// Text part of the line.
  final String text;
}
