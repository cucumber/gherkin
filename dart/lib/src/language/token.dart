import 'package:cucumber_gherkin/src/extensions/token_type_extension.dart';
import 'package:cucumber_gherkin/src/language/gherkin_dialect.dart';
import 'package:cucumber_gherkin/src/language/gherkin_line.dart';
import 'package:cucumber_gherkin/src/language/gherkin_line_span.dart';
import 'package:cucumber_gherkin/src/language/location.dart';
import 'package:cucumber_gherkin/src/language/token_type.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// A single scanned line of a Gherkin document together with the result of
/// matching it against a [TokenType].
class Token {
  /// Creates a token for the given [line] at the given [location].
  Token(this.line, this.location);

  /// The source line this token was scanned from.
  GherkinLine line;

  /// The location (line and column) of this token in the source.
  Location location;

  /// The token type assigned by the matcher.
  TokenType matchedType = TokenType.none;

  /// The localized keyword recognized on the line, if any.
  String matchedKeyword = '';

  /// The semantic type of the matched step keyword, if this is a step line.
  messages.StepKeywordType? matchedKeywordType;

  /// The text remaining on the line after the matched keyword.
  String matchedText = '';

  /// The spans (for example tags or table cells) recognized on the line.
  Iterable<GherkinLineSpan> matchedItems = const <GherkinLineSpan>[];

  /// The indentation (number of leading spaces) of the matched content.
  int matchedIndent = 0;

  /// The dialect active when this token was matched, or `null` if the token
  /// has not been matched against a dialect yet.
  GherkinDialect? matchedGherkinDialect;

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
}
