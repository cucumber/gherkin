import 'package:cucumber_gherkin/src/parser/parser.g.dart';

/// Converts [TokenType] to the corresponding rule type.
extension TokenTypeExtension on TokenType {
  /// Returns the [RuleType] that corresponds to this token type.
  ///
  /// Each lexical [TokenType] has a matching token [RuleType]. The mapping is
  /// written as an exhaustive `switch` (rather than the ordinal shortcut
  /// `RuleType.values[index]`) so that adding, removing, or reordering a
  /// [TokenType] is a compile-time error here instead of a silent, hard-to-find
  /// mismatch at runtime.
  RuleType toRuleType() {
    switch (this) {
      case TokenType.none:
        return RuleType.none;
      case TokenType.eof:
        return RuleType.eof;
      case TokenType.empty:
        return RuleType.empty;
      case TokenType.comment:
        return RuleType.comment;
      case TokenType.tagLine:
        return RuleType.tagLine;
      case TokenType.featureLine:
        return RuleType.featureLine;
      case TokenType.ruleLine:
        return RuleType.ruleLine;
      case TokenType.backgroundLine:
        return RuleType.backgroundLine;
      case TokenType.scenarioLine:
        return RuleType.scenarioLine;
      case TokenType.examplesLine:
        return RuleType.examplesLine;
      case TokenType.stepLine:
        return RuleType.stepLine;
      case TokenType.docStringSeparator:
        return RuleType.docStringSeparator;
      case TokenType.tableRow:
        return RuleType.tableRow;
      case TokenType.language:
        return RuleType.language;
      case TokenType.other:
        return RuleType.other;
    }
  }
}
