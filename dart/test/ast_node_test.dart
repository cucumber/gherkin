import 'package:cucumber_gherkin/src/ast_node.dart';
import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/parser/token.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  group('AstNode', () {
    test('returns null or an empty collection for an absent rule', () {
      final node = AstNode(RuleType.scenario);

      expect(node.getSingle<String>(RuleType.description), isNull);
      expect(node.getItems<String>(RuleType.description), isEmpty);
      expect(node.getToken(TokenType.stepLine), isNull);
      expect(node.getTokens(TokenType.stepLine), isEmpty);
    });

    test('keeps items ordered and separates them by rule', () {
      final node = AstNode(RuleType.scenario)
        ..add(RuleType.description, 'first')
        ..add(RuleType.step, 'step')
        ..add(RuleType.description, 'second');

      expect(node.getSingle<String>(RuleType.description), 'first');
      expect(node.getItems<String>(RuleType.description), ['first', 'second']);
      expect(node.getItems<String>(RuleType.step), ['step']);
    });

    test('looks up tokens using the corresponding grammar rule', () {
      final first = Token(
        GherkinLine('Given first', 1),
        const messages.Location(line: 1),
      );
      final second = Token(
        GherkinLine('Then second', 2),
        const messages.Location(line: 2),
      );
      final node = AstNode(RuleType.scenario)
        ..add(RuleType.stepLine, first)
        ..add(RuleType.stepLine, second);

      expect(node.getToken(TokenType.stepLine), same(first));
      expect(node.getTokens(TokenType.stepLine), [first, second]);
      expect(node.getTokens(TokenType.comment), isEmpty);
    });
  });
}
