import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/language/gherkin_language_constants.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

class GherkinLine {
  GherkinLine(this._lineText, this._lineNumber)
    : _trimmedLineText = _lineText.trimLeft(),
      _isEof = false;

  GherkinLine.eof()
    : _lineText = '',
      _lineNumber = _unsetLineNumber,
      _trimmedLineText = '',
      _isEof = true;

  static const int _unsetLineNumber = -1;

  static const int _offset = 1;

  static final RegExp _commentSuffix = RegExp(r'\s' + commentPrefix);

  static final RegExp _nonWhitespaceToken = RegExp(r'^\S+$');

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

  bool get isEof => _isEof;

  String getLineText([int indentToRemove = 0]) {
    if (indentToRemove < 0 || indentToRemove > indent) {
      return _trimmedLineText;
    }
    return _lineText.substring(indentToRemove);
  }

  String getRestTrimmed(int length) =>
      _trimmedLineText.substring(length).trim();

  int get indent => _lineText.length - _trimmedLineText.length;

  bool get isEmptyLine => _trimmedLineText.isEmpty;

  bool startsWith(String prefix) => _trimmedLineText.startsWith(prefix);

  bool startsWithTitleKeyword(String text) =>
      startsWith('$text$titleKeywordSeparator');

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
          messages.Location(line: _lineNumber, column: column),
        );
      }
      tags.add(GherkinLineSpan(column, tagPrefix + token));
      indexInUncommentedLine += element.length + 1;
    }

    return tags;
  }

  Iterable<GherkinLineSpan> get tableCells {
    final lineSpans = <GherkinLineSpan>[];
    var cellBuffer = StringBuffer();
    var beforeFirst = true;
    var col = 0;
    var cellStart = 0;
    var escape = false;
    for (final rune in _lineText.runes) {
      final chr = String.fromCharCode(rune);
      if (escape) {
        switch (chr) {
          case 'n':
            cellBuffer.write('\n');
          case r'\':
            cellBuffer.write(r'\');
          case tableCellSeparator:
            cellBuffer.write('|');
          default:
            cellBuffer.write(r'\');
            cellBuffer.write(chr);
        }
        escape = false;
      } else {
        switch (chr) {
          case r'\':
            escape = true;
          case tableCellSeparator:
            if (beforeFirst) {
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

class GherkinLineSpan {
  const GherkinLineSpan(this.column, this.text);

  final int column;

  final String text;
}
