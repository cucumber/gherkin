import 'package:gherkin/language.dart';
import 'package:gherkin/parser.dart';

import 'test_token_formatter.dart';
import 'no_op_result.dart';

class TokenFormatterBuilder implements IBuilder<NoOpResult> {
  final TestTokenFormatter formatter = TestTokenFormatter();
  final StringBuffer tokensTextBuilder = StringBuffer();

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
