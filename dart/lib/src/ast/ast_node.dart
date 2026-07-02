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

  /// Returns the single [Token] of [tokenType].
  ///
  /// Unlike [getToken], this throws a [StateError] when the token is absent.
  /// The grammar guarantees the token exists at the point this is called, so a
  /// missing token indicates the generated parser and this builder have drifted
  /// out of sync (e.g. `parser.g.dart` was regenerated from a changed grammar
  /// without updating the builder). Failing loudly here surfaces that as a
  /// clear diagnostic rather than a downstream null-dereference crash.
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

  /// Returns the first sub-item of [ruleType].
  ///
  /// Unlike [singleOrNull], this throws a [StateError] when no sub-item of
  /// [ruleType] is present. The grammar guarantees the sub-item exists at the
  /// point this is called, so its absence indicates the generated parser and
  /// this builder have drifted out of sync. Failing loudly here surfaces that
  /// as a clear diagnostic rather than a downstream null-dereference crash.
  T require<T>(RuleType requestedRuleType) =>
      singleOrNull<T>(requestedRuleType) ??
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
