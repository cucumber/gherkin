import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';

class AstNode {
  AstNode(this.ruleType);

  final Map<RuleType, List<Object?>> _subItems = <RuleType, List<Object?>>{};

  final RuleType ruleType;

  void add(RuleType ruleType, Object? obj) {
    (_subItems[ruleType] ??= <Object?>[]).add(obj);
  }

  T? getSingle<T>(RuleType ruleType) {
    final list = _subItems[ruleType];
    if (list == null || list.isEmpty) {
      return null;
    }
    return list.first as T;
  }

  List<T> getItems<T>(RuleType ruleType) {
    final list = _subItems[ruleType];
    if (list == null) {
      return <T>[];
    }
    return list.cast<T>();
  }

  Token? getToken(TokenType tokenType) => getSingle<Token>(tokenType.ruleType);

  List<Token> getTokens(TokenType tokenType) =>
      getItems<Token>(tokenType.ruleType);
}
