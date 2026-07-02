import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/builder.dart';
import 'package:cucumber_gherkin/src/parser/rule_type.dart';
import 'package:cucumber_gherkin/src/tokens/no_op_result.dart';
import 'package:cucumber_gherkin/src/tokens/test_token_formatter.dart';

/// A [Builder] that renders each scanned token using the shared `*.tokens`
/// text format used by the acceptance tests.
class TokenFormatterBuilder implements Builder<NoOpResult> {
  /// The formatter used to render individual tokens.
  final TestTokenFormatter formatter = TestTokenFormatter();

  /// Accumulates the rendered token lines.
  final StringBuffer tokensTextBuilder = StringBuffer();

  /// The full rendered token text accumulated so far.
  String get tokensText => tokensTextBuilder.toString();

  @override
  void build(Token token) {
    tokensTextBuilder.writeln(formatter.formatToken(token));
  }

  @override
  void endRule(RuleType ruleType) {
    // nop
  }

  @override
  void reset() {
    // nop
  }

  @override
  NoOpResult get result => NoOpResult();

  @override
  void startRule(RuleType ruleType) {
    // nop
  }
}
