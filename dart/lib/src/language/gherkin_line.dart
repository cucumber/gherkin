import 'package:characters/characters.dart';
import 'package:gherkin/core.dart';
import 'package:gherkin/exceptions.dart';
import 'package:gherkin/extensions.dart';
import 'package:gherkin/language.dart';
import 'package:gherkin/src/language/gherkin_language_constants.dart';

/// The concrete [IGherkinLine] backed by a single line of source text.
class GherkinLine with INullSafetyObject implements IGherkinLine {
  /// Creates a line from its [_lineText] at the one-based [_lineNumber].
  GherkinLine(this._lineText, this._lineNumber)
    : _trimmedLineText = _lineText.trimLeft(),
      _isEof = false;

  /// Creates the sentinel line that marks the end of the file.
  GherkinLine.eof()
    : _lineText = Strings.empty,
      _lineNumber = Int.min,
      _trimmedLineText = Strings.empty,
      _isEof = true;
  // Columns are 1-indexed.
  static const int _offset = 1;

  final String _lineText;
  final int _lineNumber;
  final String _trimmedLineText;
  final bool _isEof;

  // A concrete line is never the empty sentinel; only [IGherkinLine.empty]
  // (the private [_EmptyGherkinLine]) reports itself as empty.
  @override
  bool get isEmpty => false;

  @override
  bool get isEof => _isEof;

  @override
  bool get isNotEof => !isEof;

  /// NOP
  @override
  void detach() {}

  /// The one-based line number of this line in the source.
  int get lineNumber => _lineNumber;

  @override
  String getLineText([int indentToRemove = 0]) {
    if (indentToRemove < 0 || indentToRemove > indent) {
      return _trimmedLineText;
    }
    return _lineText.substring(indentToRemove);
  }

  @override
  String getRestTrimmed(int length) =>
      _trimmedLineText.substring(length).trim();

  @override
  int get indent => _lineText.length - _trimmedLineText.length;

  @override
  bool get isEmptyLine => _trimmedLineText.isEmpty;

  @override
  bool startsWith(String prefix) => _trimmedLineText.startsWith(prefix);

  @override
  bool startsWithTitleKeyword(String text) {
    final textLength = text.length;
    if (_trimmedLineText.length <= textLength) {
      return false;
    }
    final b2 = _trimmedLineText.startsWith(text);
    const separatorLength =
        GherkinLanguageConstants.titleKeywordSeparator.length;
    final substr = _trimmedLineText.substring(
      textLength,
      textLength + separatorLength,
    );
    final b3 = substr == GherkinLanguageConstants.titleKeywordSeparator;
    return b2 && b3;
  }

  @override
  Iterable<GherkinLineSpan> get tags {
    final tags = <GherkinLineSpan>[];
    final pattern = RegExp(r'\s' + GherkinLanguageConstants.commentPrefix);
    final parts = _trimmedLineText.splitWithLimit(pattern, limit: 2);
    final uncommentedLine = parts[0];

    var indexInUncommentedLine = 0;
    final elements = uncommentedLine.split(GherkinLanguageConstants.tagPrefix);

    for (final element in elements) {
      final token = element.rtrim();
      if (token.isEmpty) {
        continue;
      }
      final symbolLength =
          uncommentedLine.substring(0, indexInUncommentedLine).length;
      final column = indent + symbolLength + 1;
      final subPattern = RegExp(r'^\S+$');
      if (!subPattern.hasMatch(token)) {
        throw ParserException(
          'A tag may not contain whitespace',
          Location(lineNumber, column),
        );
      }
      tags.add(
        GherkinLineSpan(column, GherkinLanguageConstants.tagPrefix + token),
      );
      indexInUncommentedLine += element.length + 1;
    }

    return tags;
  }

  @override
  Iterable<GherkinLineSpan> get tableCells {
    final lineSpans = <GherkinLineSpan>[];
    var cellBuffer = StringBuffer();
    var beforeFirst = true;
    var col = 0;
    var cellStart = 0;
    var escape = false;
    final iterator = _lineText.characters;
    for (final chr in iterator) {
      if (escape) {
        switch (chr) {
          case GherkinLanguageConstants.tableCellNewLineEscape:
            cellBuffer.write('\n');
          case GherkinLanguageConstants.tableCellEscapeChar:
            cellBuffer.write(r'\');
          case GherkinLanguageConstants.tableCellSeparator:
            cellBuffer.write('|');
          default:
            // Invalid escape. We'll just ignore it.
            cellBuffer.write(r'\');
            cellBuffer.write(chr);
        }
        escape = false;
      } else {
        switch (chr) {
          case GherkinLanguageConstants.tableCellEscapeChar:
            escape = true;
          case GherkinLanguageConstants.tableCellSeparator:
            if (beforeFirst) {
              // Skip the first empty span
              beforeFirst = false;
            } else {
              final cell = cellBuffer.toString();
              final leftTrimmedCell = cell.ltrimKeepNewLines();
              final cellIndent = cell.length - leftTrimmedCell.length;
              final column = cellStart + cellIndent + _offset;
              final text = leftTrimmedCell.rtrimKeepNewLines();
              final lineSpan = GherkinLineSpan(column, text);
              lineSpans.add(lineSpan);
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

/// Returns true if rune represents a whitespace character.
///
/// The definition of whitespace matches that used in String.trim which is based
/// on Unicode 6.2. This maybe be a different set of characters than the
/// environment's RegExp definition for whitespace, which is given by the
/// ECMAScript standard: http://ecma-international.org/ecma-262/5.1/#sec-15.10
///
/// (c) https://pub.dev/documentation/quiver/latest/quiver.strings/isWhitespace.html
bool isWhitespace(int rune) =>
    (rune >= 0x0009 && rune <= 0x000D) || // TAB, CR
    rune == 0x0020 || // SPC
    rune == 0x0085 || // Next line
    rune == 0x00A0 || // No-break space
    rune == 0x1680 ||
    rune == 0x180E ||
    (rune >= 0x2000 && rune <= 0x200A) ||
    rune == 0x2028 ||
    rune == 0x2029 ||
    rune == 0x202F ||
    rune == 0x205F ||
    rune == 0x3000 ||
    rune == 0xFEFF;
