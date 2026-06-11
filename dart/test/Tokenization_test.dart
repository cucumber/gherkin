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

    for (final file in files) {
      final fullPathToTestFeatureFile = file.path.replaceAll(r'\', '/');
      final tokenMatcher =
          fullPathToTestFeatureFile.endsWith('.md')
              ? MarkdownTokenMatcher(dialectProvider)
              : TokenMatcher(dialectProvider);
      final expectedTokensFile = '$fullPathToTestFeatureFile.tokens';

      final tokensText = TokensGenerator.generateTokens(
        fullPathToTestFeatureFile,
        tokenMatcher,
      );
      final tokens = await File(expectedTokensFile).readAsString();
      final expectedTokensText = LineEndingHelper.normalizeLineEndings(tokens);

      expect(
        tokensText,
        expectedTokensText,
        reason: 'Tokens mismatch for $expectedTokensFile',
      );
    }
  });
}
