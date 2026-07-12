import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';

/// A node in the parse tree built during a `Builder` walk.
class AstNode {
  /// Creates a node for the given [ruleType].
  AstNode(this.ruleType);

  final Map<RuleType, List<Object?>> _subItems = <RuleType, List<Object?>>{};

  /// The grammar [RuleType] this node represents.
  final RuleType ruleType;

  /// Records [obj] under [ruleType].
  void add(RuleType ruleType, Object? obj) {
    (_subItems[ruleType] ??= <Object?>[]).add(obj);
  }

  /// Returns the first value for [ruleType], or `null` if none.
  T? getSingle<T>(RuleType ruleType) {
    final list = _subItems[ruleType];
    if (list == null || list.isEmpty) {
      return null;
    }
    return list.first as T;
  }

  /// Returns all values for [ruleType], cast to [T].
  List<T> getItems<T>(RuleType ruleType) {
    final list = _subItems[ruleType];
    if (list == null) {
      return <T>[];
    }
    return list.cast<T>();
  }

  /// Returns the first [Token] of [tokenType], or `null` if absent.
  Token? getToken(TokenType tokenType) => getSingle<Token>(tokenType.ruleType);

  /// Returns all [Token]s of [tokenType].
  List<Token> getTokens(TokenType tokenType) =>
      getItems<Token>(tokenType.ruleType);
}
