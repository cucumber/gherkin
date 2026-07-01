import 'package:gherkin/src/language/token.dart';
import 'package:gherkin/src/parser/rule_type.dart';

/// Assembles a result of type [T] from the events emitted by the parser.
abstract class Builder<T> {
  /// Handles a recognized [token].
  void build(Token token);

  /// Begins a grammar rule of the given [ruleType].
  void startRule(RuleType ruleType);

  /// Ends the current grammar rule of the given [ruleType].
  void endRule(RuleType ruleType);

  /// The assembled result, valid after a full parse.
  T get result;

  /// Resets the builder so it can be reused for another parse.
  void reset();
}
