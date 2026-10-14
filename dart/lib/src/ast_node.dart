import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/parser/token.dart';

/// A parse-tree node for one grammar rule and the items collected under it.
class AstNode {
  /// Creates a node for [ruleType].
  AstNode(this.ruleType);

  final Map<RuleType, List<Object?>> _subItems = <RuleType, List<Object?>>{};

  /// The grammar rule this node represents.
  final RuleType ruleType;

  /// Adds [obj] under [ruleType].
  void add(RuleType ruleType, Object? obj) {
    (_subItems[ruleType] ??= <Object?>[]).add(obj);
  }

  /// The first item stored under [ruleType], or `null` if there are none.
  T? getSingle<T>(RuleType ruleType) {
    final list = _subItems[ruleType];
    if (list == null || list.isEmpty) {
      return null;
    }
    return list.first as T;
  }

  /// The items stored under [ruleType].
  ///
  /// Returns an empty list when [ruleType] has no items.
  List<T> getItems<T>(RuleType ruleType) {
    final list = _subItems[ruleType];
    if (list == null) {
      return <T>[];
    }
    return list.cast<T>();
  }

  /// The token matched as [tokenType], or `null` if there is none.
  Token? getToken(TokenType tokenType) => getSingle<Token>(tokenType.ruleType);

  /// The tokens matched as [tokenType].
  List<Token> getTokens(TokenType tokenType) =>
      getItems<Token>(tokenType.ruleType);
}
