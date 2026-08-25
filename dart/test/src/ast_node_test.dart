import 'package:cucumber_gherkin/src/ast_node.dart';
import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/parser/token.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  test('stores typed AST values and tokens', () {
    final node = AstNode(RuleType.feature);
    final token = Token(
      GherkinLine('Feature: value', 1),
      const messages.Location(line: 1),
    );

    expect(node.getSingle<String>(RuleType.description), isNull);
    expect(node.getItems<String>(RuleType.description), isEmpty);
    node.add(RuleType.description, 'description');
    node.add(TokenType.featureLine.ruleType, token);
    expect(node.getSingle<String>(RuleType.description), 'description');
    expect(node.getToken(TokenType.featureLine), same(token));
  });
}
