import 'dart:io';

import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:cucumber_gherkin/src/language/gherkin_dialect_provider.dart';
import 'package:cucumber_gherkin/src/language/gherkin_token_matcher.dart';
import 'package:test/test.dart';

import '../../../tool/line_ending_helper.dart';
import '../../../tool/tokens_generator.dart';

void main() {
  test('Test successful token matching', () async {
    const languages = builtinDialects;
    final path = Directory('../testdata/good');
    final files = path.listSync().where(
      (file) => file.path.endsWith('.feature'),
    );

    final dialectProvider = GherkinDialectProvider(languages);

    for (final file in files) {
      final fullPathToTestFeatureFile = file.path.replaceAll(r'\', '/');
      final expectedTokensFile = '$fullPathToTestFeatureFile.tokens';

      final tokensText = TokensGenerator.generateTokens(
        fullPathToTestFeatureFile,
        GherkinTokenMatcher(dialectProvider),
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
