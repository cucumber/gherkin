import 'dart:convert';
import 'dart:io';

import 'package:gherkin/helpers.dart';
import 'package:gherkin/language.dart';
import 'package:gherkin/tokens.dart';
import 'package:test/test.dart';

void main() {
  test('Test successful token matching', () async {
    final languages = loadGherkinLanguagesFromJsonAsset();
    final path = Directory('../testdata/good');
    final files = path.listSync().where(
      (file) =>
          file.path.endsWith('.feature') || file.path.endsWith('.feature.md'),
    );

    final dialectProvider = GherkinDialectProvider(languages);

    for (var file in files) {
      var fullPathToTestFeatureFile = file.path.replaceAll('\\', '/');
      final tokenMatcher =
          fullPathToTestFeatureFile.endsWith('.md')
              ? MarkdownTokenMatcher(dialectProvider)
              : TokenMatcher(dialectProvider);
      var expectedTokensFile = '$fullPathToTestFeatureFile.tokens';

      print('Validating $expectedTokensFile ...');

      var tokensText = TokensGenerator.generateTokens(
        fullPathToTestFeatureFile,
        tokenMatcher,
      );
      var tokens = await File(expectedTokensFile).readAsString(encoding: utf8);
      var expectedTokensText = LineEndingHelper.normalizeLineEndings(tokens);

      expect(tokensText, expectedTokensText);
    }
  });
}
