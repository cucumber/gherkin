import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:gherkin/core.dart';
import 'package:gherkin/extensions.dart';
import 'package:gherkin/src/language/gherkin_line_span.dart';
import 'package:gherkin/src/language/i_gherkin_dialect.dart';
import 'package:gherkin/src/language/i_gherkin_line.dart';
import 'package:gherkin/src/language/location.dart';
import 'package:gherkin/src/language/token_type.dart';

/// A single scanned line of a Gherkin document together with the result of
/// matching it against a [TokenType].
class Token with INullSafetyObject {
  /// Creates a token for the given [line] at the given [location].
  Token(this.line, this.location);

  /// A sentinel token representing an invalid/absent line.
  static Token get empty => _InvalidToken();

  /// The source line this token was scanned from.
  IGherkinLine line = IGherkinLine.empty;

  /// The location (line and column) of this token in the source.
  Location location = Location.empty;

  /// The token type assigned by the matcher.
  TokenType matchedType = TokenType.none;

  /// The localized keyword recognized on the line, if any.
  String matchedKeyword = Strings.empty;

  /// The semantic type of the matched step keyword, if this is a step line.
  messages.StepKeywordType? matchedKeywordType;

  /// The text remaining on the line after the matched keyword.
  String matchedText = Strings.empty;

  /// The spans (for example tags or table cells) recognized on the line.
  Iterable<GherkinLineSpan> matchedItems = const <GherkinLineSpan>[];

  /// The indentation (number of leading spaces) of the matched content.
  int matchedIndent = 0;

  /// The dialect active when this token was matched.
  IGherkinDialect matchedGherkinDialect = IGherkinDialect.empty;

  /// Whether this token marks the end of the file.
  bool get isEof => line.isEof;

  /// The textual value of the token, or `'EOF'` at the end of the file.
  String get tokenValue => isEof ? 'EOF' : line.getLineText(-1);

  /// Releases any resources held by the underlying [line].
  void detach() {
    if (line.isNotEof) {
      line.detach();
    }
  }

  @override
  String toString() => '${matchedType.wireName}: $matchedKeyword/$matchedText';

  // A concrete token is never the empty sentinel; only [Token.empty]
  // (the private [_InvalidToken]) reports itself as empty.
  @override
  bool get isEmpty => false;
}

/// Convenience implementation of an invalid [Token] instance.
class _InvalidToken extends Token {
  _InvalidToken() : super(IGherkinLine.empty, Location.empty) {
    matchedGherkinDialect = IGherkinDialect.empty;
    matchedType = TokenType.none;
    matchedKeyword = Strings.empty;
    matchedText = Strings.empty;
    matchedItems = const <GherkinLineSpan>[];
    matchedIndent = 0;
  }

  @override
  bool get isEmpty => true;
}
