import 'package:cucumber_gherkin/src/gherkin_document_builder.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:test/test.dart';

void main() {
  test('retains grammar helper nodes that need no transformation', () {
    final builder = GherkinDocumentBuilder(() => 'id');

    builder.startRule(RuleType.tags);
    builder.endRule(RuleType.tags);

    expect(builder.result.feature, isNull);
  });
}
