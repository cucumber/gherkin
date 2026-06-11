import 'dart:io';

import 'package:gherkin/language.dart';
import 'package:gherkin/parser.dart';
import 'package:gherkin/src/ast/messages_gherkin_document_builder.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  final idGenerator = IdGenerator.incrementingGenerator;
  final languages = loadGherkinLanguagesFromJsonAsset();

  test('Test successful parsing', () async {
    var dialectProvider = GherkinDialectProvider(languages);

    var matcher = TokenMatcher(dialectProvider);

    final goodDir = Directory('../testdata/good');

    final filesEntities = goodDir.listSync().where(
      (file) =>
          file.path.endsWith('.feature') || file.path.endsWith('.feature.md'),
    );

    var builder = MessagesGherkinDocumentBuilder(idGenerator);

    var parser = Parser<messages.GherkinDocument>(builder);

    for (var fileEntity in filesEntities) {
      print('Validating ${fileEntity.path.replaceAll('\\', '/')} ...');

      var file = File(fileEntity.path);

      final tokenScanner = FileTokenScanner.fromFile(file);
      final matcherForFile =
          fileEntity.path.endsWith('.md')
              ? MarkdownTokenMatcher(dialectProvider)
              : matcher;

      var parsingResult = parser.parse(tokenScanner, matcherForFile);

      expect(parsingResult, isNotNull);
    }
  });
}
