import 'package:cucumber_gherkin/src/gherkin_document_builder.dart';
import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/parser/token.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  late GherkinDocumentBuilder builder;

  setUp(() {
    builder = GherkinDocumentBuilder(() => 'unused');
  });

  group('GherkinDocumentBuilder.reset', () {
    test('discards a completed result and its comments', () {
      final previous = _buildCommentDocument(builder, '# previous');

      builder.reset();

      expect(builder.result.feature, isNull);
      expect(builder.result.comments, isEmpty);

      final next = _buildCommentDocument(builder, '# next');
      expect(next.comments.single.text, '# next');
      expect(previous.comments.single.text, '# previous');
    });

    test('discards unfinished rules and comments', () {
      builder
        ..startRule(RuleType.gherkinDocument)
        ..startRule(RuleType.feature)
        ..build(_comment('# abandoned'))
        ..reset();

      final document = _buildCommentDocument(builder, '# fresh');

      expect(document.feature, isNull);
      expect(document.comments.single.text, '# fresh');
    });
  });
}

messages.GherkinDocument _buildCommentDocument(
  GherkinDocumentBuilder builder,
  String text,
) {
  builder
    ..startRule(RuleType.gherkinDocument)
    ..build(_comment(text))
    ..endRule(RuleType.gherkinDocument);
  return builder.result;
}

Token _comment(String text) =>
    Token(GherkinLine(text, 1), const messages.Location(line: 1, column: 1))
      ..matchedType = TokenType.comment
      ..matchedText = text;
