import 'package:cucumber_gherkin/src/gherkin_document_builder.dart';
import 'package:cucumber_gherkin/src/ast_node.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:test/test.dart';

void main() {
  test('retains grammar helper nodes that need no transformation', () {
    final builder = GherkinDocumentBuilder(() => 'id');

    builder.startRule(RuleType.tags);
    builder.endRule(RuleType.tags);

    expect(builder.result.feature, isNull);
    expect(builder.transformNode(AstNode(RuleType.tags)), isA<AstNode>());
    expect(
      builder.transformNode(AstNode(RuleType.descriptionHelper)),
      isA<AstNode>(),
    );
  });
}
