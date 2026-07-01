import 'package:cucumber_gherkin/src/extensions/token_type_extension.dart';
import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/language/token_type.dart';
import 'package:cucumber_gherkin/src/parser/rule_type.dart';

/// A node in the intermediate parse tree, grouping the sub-items recognized
/// for a single [RuleType].
class AstNode {
  /// Creates a node for the given [ruleType].
  AstNode(this.ruleType);

  final Map<RuleType, List<dynamic>> _subItems = <RuleType, List<dynamic>>{};

  /// The grammar rule this node represents.
  final RuleType ruleType;

  /// Returns the single [Token] of [tokenType], or `null` if absent.
  Token? getToken(TokenType tokenType) =>
      singleOrNull<Token>(tokenType.toRuleType());

  /// Returns all [Token]s of the given [tokenType] held by this node.
  Iterable<Token> getTokens(TokenType tokenType) =>
      items<Token>(tokenType.toRuleType());

  /// Adds [obj] to the list of sub-items stored under [ruleType].
  void add<T>(RuleType ruleType, T obj) {
    final list = _subItems[ruleType];
    if (list == null) {
      _subItems[ruleType] = [obj];
    } else {
      list.add(obj);
    }
  }

  /// Returns the first sub-item of [ruleType], or `null` if there is none.
  T? singleOrNull<T>(RuleType ruleType) {
    final elems = items<T>(ruleType);
    if (elems.isEmpty) {
      return null;
    }
    return elems.first;
  }

  /// Returns the first sub-item of [ruleType], or [defaultValue] if there is
  /// none.
  T singleOrDefault<T>(RuleType ruleType, T defaultValue) =>
      singleOrNull<T>(ruleType) ?? defaultValue;

  /// Returns all sub-items stored under [ruleType], cast to type [T].
  List<T> items<T>(RuleType ruleType) {
    final list = _subItems[ruleType];
    if (list == null) {
      return <T>[];
    }
    return list.cast<T>();
  }
}
