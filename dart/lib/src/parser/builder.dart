import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/parser/token.dart';

abstract class Builder<T> {
  void build(Token token);

  void startRule(RuleType ruleType);

  void endRule(RuleType ruleType);

  T get result;

  void reset();
}
