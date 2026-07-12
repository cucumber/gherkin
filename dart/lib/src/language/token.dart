import 'package:cucumber_gherkin/src/language/gherkin_line.dart';
import 'package:cucumber_gherkin/src/language/location.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// A single scanned line of a Gherkin document together with the result of
/// matching it against a [TokenType].
class Token {
  /// Creates a token for the given [line] at the given [location].
  Token(this.line, this.location);

  /// The source line this token was scanned from.
  final GherkinLine line;

  /// The location of this token in the source.
  ///
  /// Set by the scanner with column `0` initially; updated by the matcher to
  /// a one-based column when the token is classified.
  Location location;

  /// The token type assigned by the matcher.
  TokenType matchedType = TokenType.none;

  /// The matched keyword or delimiter, if any.
  ///
  /// Localized Gherkin keywords for title and step lines; the doc-string
  /// delimiter for doc-string separator lines; otherwise empty.
  String matchedKeyword = '';

  /// The semantic type of the matched step keyword, if this is a step line.
  messages.StepKeywordType? matchedKeywordType;

  /// Match-specific payload text set by the matcher.
  ///
  /// For title and step lines, the remainder after the matched keyword. For
  /// comment lines, the full line text. For language headers, the language
  /// tag. For doc-string separators, the media type (open) or empty (close).
  /// Empty for tag lines, table rows, blank lines, and EOF.
  String matchedText = '';

  /// The spans (for example tags or table cells) recognized on the line.
  Iterable<GherkinLineSpan> matchedItems = const <GherkinLineSpan>[];

  /// The language tag active when this Feature line was matched, or `null`
  /// for other token types.
  String? matchedLanguage;

  /// Whether this token marks the end of the file.
  bool get isEof => line.isEof;

  /// The textual value of the token, or `'EOF'` at the end of the file.
  String get tokenValue => isEof ? 'EOF' : line.getLineText(-1);

  /// Releases any resources held by the underlying [line].
  void detach() => line.detach();
}
