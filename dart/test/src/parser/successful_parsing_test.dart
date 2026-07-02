import 'dart:io';

import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:cucumber_gherkin/src/ast/messages_gherkin_document_builder.dart';
import 'package:cucumber_gherkin/src/language/file_token_scanner.dart';
import 'package:cucumber_gherkin/src/language/gherkin_dialect_provider.dart';
import 'package:cucumber_gherkin/src/language/gherkin_languages_loader.dart';
import 'package:cucumber_gherkin/src/language/gherkin_token_matcher.dart';
import 'package:cucumber_gherkin/src/gherkin/id_generator.dart';
import 'package:cucumber_gherkin/src/language/markdown_token_matcher.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/parser/token_matcher.dart';
import 'package:test/test.dart';

void main() {
  final idGenerator = IdGenerator.incrementingGenerator;
  final languages = builtinGherkinDialects();

  test('Test successful parsing', () async {
    final dialectProvider = GherkinDialectProvider(languages);

    final matcher = GherkinTokenMatcher(dialectProvider);

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
      final TokenMatcher matcherForFile =
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
