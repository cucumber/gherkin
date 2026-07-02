import 'package:cucumber_gherkin/src/language/token_type.dart';
import 'package:cucumber_gherkin/src/parser/rule_type.dart';

/// Conversions from [TokenType] to its wire name and corresponding rule type.
extension TokenTypeExtension on TokenType {
  /// The canonical wire name of this token type, as emitted in the `*.tokens`
  /// acceptance format and shared with the other Gherkin implementations.
  ///
  /// This is intentionally decoupled from the (lowerCamelCase) Dart enum
  /// identifier so the output format stays stable.
  String get wireName {
    switch (this) {
      case TokenType.none:
        return 'None';
      case TokenType.eof:
        return 'EOF';
      case TokenType.empty:
        return 'Empty';
      case TokenType.comment:
        return 'Comment';
      case TokenType.tagLine:
        return 'TagLine';
      case TokenType.featureLine:
        return 'FeatureLine';
      case TokenType.ruleLine:
        return 'RuleLine';
      case TokenType.backgroundLine:
        return 'BackgroundLine';
      case TokenType.scenarioLine:
        return 'ScenarioLine';
      case TokenType.examplesLine:
        return 'ExamplesLine';
      case TokenType.stepLine:
        return 'StepLine';
      case TokenType.docStringSeparator:
        return 'DocStringSeparator';
      case TokenType.tableRow:
        return 'TableRow';
      case TokenType.language:
        return 'Language';
      case TokenType.other:
        return 'Other';
    }
  }

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
