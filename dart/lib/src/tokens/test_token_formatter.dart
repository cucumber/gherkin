import 'package:gherkin/extensions.dart';
import 'package:gherkin/language.dart';

/// Renders a [Token] in the shared `*.tokens` text format used by the
/// acceptance tests.
class TestTokenFormatter {
  /// Returns the single-line `*.tokens` representation of [token].
  String formatToken(Token token) {
    if (token.isEof) {
      return 'EOF';
    }
    final items = token.matchedItems.map(
      (element) => '${element.column}:${element.text}',
    );
    final matchedItems = items.isEmpty ? '' : items.join(',');
    final matchedType = token.matchedType.wireName;
    final matchedKeyword =
        token.matchedKeyword.isEmpty ? '' : token.matchedKeyword;
    final matchedKeywordType =
        matchedKeyword.isEmpty
            ? ''
            : token.matchedKeywordType == null
            ? '()'
            : '(${token.matchedKeywordType!.value})';
    final matchedText = token.matchedText.isEmpty ? '' : token.matchedText;
    return '(${token.location.line}:${token.location.column})'
        '$matchedType:$matchedKeywordType$matchedKeyword/$matchedText/$matchedItems';
  }
}
