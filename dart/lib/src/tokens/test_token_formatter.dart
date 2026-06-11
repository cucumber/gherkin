import 'package:gherkin/extensions.dart';
import 'package:gherkin/language.dart';

class TestTokenFormatter {
  String formatToken(Token token) {
    if (token.isEof) {
      return 'EOF';
    }
    var items = token.matchedItems.map(
      (element) => '${element.column}:${element.text}',
    );
    var matchedItems = items.isEmpty ? '' : items.join(',');
    var matchedType = token.matchedType.wireName;
    var matchedKeyword =
        token.matchedKeyword.isEmpty ? '' : token.matchedKeyword;
    var matchedKeywordType =
        matchedKeyword.isEmpty
            ? ''
            : token.matchedKeywordType == null
            ? '()'
            : '(${token.matchedKeywordType!.value})';
    var matchedText = token.matchedText.isEmpty ? '' : token.matchedText;
    return '(${token.location.line}:${token.location.column})'
        '$matchedType:$matchedKeywordType$matchedKeyword/$matchedText/$matchedItems';
  }
}
