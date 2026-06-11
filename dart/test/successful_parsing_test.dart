import 'dart:io';

import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:gherkin/language.dart';
import 'package:gherkin/parser.dart';
import 'package:gherkin/src/ast/messages_gherkin_document_builder.dart';
import 'package:test/test.dart';

void main() {
  final idGenerator = IdGenerator.incrementingGenerator;
  final languages = loadGherkinLanguagesFromJsonAsset();

  test('Test successful parsing', () async {
    final dialectProvider = GherkinDialectProvider(languages);

    final matcher = TokenMatcher(dialectProvider);

    final goodDir = Directory('../testdata/good');

    final filesEntities = goodDir.listSync().where(
      (file) =>
          file.path.endsWith('.feature') || file.path.endsWith('.feature.md'),
    );

    final builder = MessagesGherkinDocumentBuilder(idGenerator);

    final parser = Parser<messages.GherkinDocument>(builder);

    for (final fileEntity in filesEntities) {
      final normalizedPath = fileEntity.path.replaceAll(r'\', '/');

      final file = File(fileEntity.path);

      final tokenScanner = FileTokenScanner.fromFile(file);
      final matcherForFile =
          fileEntity.path.endsWith('.md')
              ? MarkdownTokenMatcher(dialectProvider)
              : matcher;

      final parsingResult = parser.parse(tokenScanner, matcherForFile);

      expect(
        parsingResult,
        isNotNull,
        reason: 'Failed to parse $normalizedPath',
      );
    }
  });
}
