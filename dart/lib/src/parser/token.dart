import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// A scanned source line together with the data recorded by matching it.
class Token {
  /// Creates a token for [line] at [location].
  Token(this.line, this.location);

  /// Creates an end-of-file token at [location].
  Token.eof(this.location) : line = null;

  /// The scanned line, or `null` for an end-of-file token.
  final GherkinLine? line;

  /// The source position of this token.
  messages.Location location;

  /// The [TokenType] assigned by a successful match.
  TokenType matchedType = TokenType.none;

  /// The keyword text captured by the match, or an empty string.
  String matchedKeyword = '';

  /// The step keyword category when this token is a step.
  messages.StepKeywordType? matchedKeywordType;

  /// The text captured by the match.
  String matchedText = '';

  /// Items captured by the match, such as tags or table cells.
  Iterable<GherkinLineSpan> matchedItems = const <GherkinLineSpan>[];

  /// The dialect name captured when this token matched a feature line.
  String? matchedLanguage;

  /// Whether this token marks the end of the source.
  bool get isEof => line == null;

  /// The trimmed line text, or `EOF` when [isEof] is true.
  String get tokenValue => isEof ? 'EOF' : line!.getLineText(-1);
}
