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
  RuleType toRuleType() => RuleType.values[index];
}
