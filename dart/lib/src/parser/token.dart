import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

class Token {
  Token(this.line, this.location);

  Token.eof(this.location) : line = null;

  final GherkinLine? line;

  messages.Location location;

  TokenType matchedType = TokenType.none;

  String matchedKeyword = '';

  messages.StepKeywordType? matchedKeywordType;

  String matchedText = '';

  Iterable<GherkinLineSpan> matchedItems = const <GherkinLineSpan>[];

  String? matchedLanguage;

  bool get isEof => line == null;

  String get tokenValue => isEof ? 'EOF' : line!.getLineText(-1);
}
