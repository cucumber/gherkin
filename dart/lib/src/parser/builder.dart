import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/parser/token.dart';

/// Receives matched tokens and grammar-rule boundaries.
///
/// [T] is the value exposed by [result].
abstract class Builder<T> {
  /// Accepts a matched [token].
  void build(Token token);

  /// Starts a nested rule of [ruleType].
  void startRule(RuleType ruleType);

  /// Ends the current rule of [ruleType].
  void endRule(RuleType ruleType);

  /// The value built from the tokens accepted so far.
  T get result;

  /// Discards built state so this builder can parse another source.
  void reset();
}
