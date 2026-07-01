import 'package:gherkin/core.dart';
import 'package:gherkin/extensions.dart';
import 'package:gherkin/language.dart';
import 'package:gherkin/parser.dart';

/// A node in the intermediate parse tree, grouping the sub-items recognized
/// for a single [RuleType].
class AstNode with INullSafetyObject {
  /// Creates a node for the given [ruleType].
  AstNode(this.ruleType);

  /// A sentinel node representing an invalid/absent node.
  static AstNode empty = _InvalidAstNode();

  final Map<RuleType, List<dynamic>> _subItems = <RuleType, List<dynamic>>{};

  /// The grammar rule this node represents.
  final RuleType ruleType;

  /// Returns the single [Token] of [tokenType], or [Token.empty] if absent.
  Token getToken(TokenType tokenType) =>
      singleOrDefault<Token>(tokenType.toRuleType(), Token.empty);

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

  /// Returns the first sub-item of [ruleType], or [emptyValue] if there is
  /// none.
  T singleOrDefault<T>(RuleType ruleType, T emptyValue) {
    final elems = items<T>(ruleType);
    if (elems.isEmpty) {
      return emptyValue;
    }
    return elems.first;
  }

  /// Returns all sub-items stored under [ruleType], cast to type [T].
  List<T> items<T>(RuleType ruleType) {
    final list = _subItems[ruleType];
    if (list == null) {
      return <T>[];
    }
    return list.cast<T>();
  }

  // A concrete node is never the empty sentinel; only [AstNode.empty]
  // (the private [_InvalidAstNode]) reports itself as empty.
  @override
  bool get isEmpty => false;
}

/// Convenience implementation of an invalid [AstNode] instance.
class _InvalidAstNode extends AstNode {
  _InvalidAstNode() : super(RuleType.none);

  @override
  bool get isEmpty => true;
}
