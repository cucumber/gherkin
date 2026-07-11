import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';

/// A node in the intermediate parse tree.
class AstNode {
  /// Creates a node for the given [ruleType].
  AstNode(this.ruleType);

  final Map<RuleType, List<Object?>> _subItems = <RuleType, List<Object?>>{};

  /// The grammar rule this node represents.
  final RuleType ruleType;

  /// Adds [obj] to the list of sub-items stored under [ruleType].
  void add(RuleType ruleType, Object? obj) {
    (_subItems[ruleType] ??= <Object?>[]).add(obj);
  }

  /// Returns the first sub-item of [ruleType], or `null` if there is none.
  T? getSingle<T>(RuleType ruleType) {
    final list = _subItems[ruleType];
    if (list == null || list.isEmpty) {
      return null;
    }
    return list.first as T;
  }

  /// Returns all sub-items stored under [ruleType], cast to type [T].
  List<T> getItems<T>(RuleType ruleType) {
    final list = _subItems[ruleType];
    if (list == null) {
      return <T>[];
    }
    return list.cast<T>();
  }

  /// Returns the first [Token] of [tokenType], or `null` if absent.
  Token? getToken(TokenType tokenType) => getSingle<Token>(tokenType.ruleType);

  /// Returns all [Token]s of the given [tokenType] held by this node.
  List<Token> getTokens(TokenType tokenType) =>
      getItems<Token>(tokenType.ruleType);
}
