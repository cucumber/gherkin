import 'package:gherkin/language.dart';
import 'package:gherkin/parser.dart';
import 'package:gherkin/src/tokens/no_op_result.dart';
import 'package:gherkin/src/tokens/test_token_formatter.dart';

/// An [IBuilder] that renders each scanned token using the shared `*.tokens`
/// text format used by the acceptance tests.
class TokenFormatterBuilder implements IBuilder<NoOpResult> {
  /// The formatter used to render individual tokens.
  final TestTokenFormatter formatter = TestTokenFormatter();

  /// Accumulates the rendered token lines.
  final StringBuffer tokensTextBuilder = StringBuffer();

  /// Returns the full rendered token text accumulated so far.
  String getTokensText() {
    return tokensTextBuilder.toString();
  }

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
