import 'package:cucumber_gherkin/src/extensions/token_type_extension.dart';
import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';

/// A node in the intermediate parse tree.
class AstNode {
  /// Creates a node for the given [ruleType].
  AstNode(this.ruleType);

  final Map<RuleType, List<Object?>> _subItems = <RuleType, List<Object?>>{};

  /// The grammar rule this node represents.
  final RuleType ruleType;

  /// Returns the first [Token] of [tokenType], or `null` if absent.
  Token? getToken(TokenType tokenType) =>
      firstOrNull<Token>(tokenType.toRuleType());

  /// Returns the single [Token] of [tokenType].
  Token requireToken(TokenType tokenType) =>
      getToken(tokenType) ??
      (throw StateError(
        'Parser/builder drift: expected a $tokenType token under $ruleType '
        'but none was present. The generated parser (parser.g.dart) and the '
        'document builder are out of sync.',
      ));

  /// Returns all [Token]s of the given [tokenType] held by this node.
  Iterable<Token> getTokens(TokenType tokenType) =>
      items<Token>(tokenType.toRuleType());

  /// Adds [obj] to the list of sub-items stored under [ruleType].
  void add(RuleType ruleType, Object? obj) {
    (_subItems[ruleType] ??= <Object?>[]).add(obj);
  }

  /// Returns the first sub-item of [ruleType], or `null` if there is none.
  T? firstOrNull<T>(RuleType ruleType) {
    final elems = items<T>(ruleType);
    if (elems.isEmpty) {
      return null;
    }
    return elems.first;
  }

  /// Returns the first sub-item of [ruleType], or [defaultValue] if there is
  /// none.
  T firstOrDefault<T>(RuleType ruleType, T defaultValue) =>
      firstOrNull<T>(ruleType) ?? defaultValue;

  /// Returns the first sub-item of [ruleType].
  T require<T>(RuleType requestedRuleType) =>
      firstOrNull<T>(requestedRuleType) ??
      (throw StateError(
        'Parser/builder drift: expected a $requestedRuleType sub-item under '
        '$ruleType but none was present. The generated parser (parser.g.dart) '
        'and the document builder are out of sync.',
      ));

  /// Returns all sub-items stored under [ruleType], cast to type [T].
  List<T> items<T>(RuleType ruleType) {
    final list = _subItems[ruleType];
    if (list == null) {
      return <T>[];
    }
    return list.cast<T>();
  }
}
