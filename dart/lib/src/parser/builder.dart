import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';

/// Assembles a result of type [T] from the events emitted by the parser.
abstract class Builder<T> {
  /// Handles a recognized [Token].
  void build(Token token);

  /// Begins a grammar rule of type [RuleType].
  void startRule(RuleType ruleType);

  /// Ends the current grammar rule of type [RuleType].
  void endRule(RuleType ruleType);

  /// The assembled result, valid after a full parse.
  T get result;

  /// Resets the builder so it can be reused for another parse.
  void reset();
}
