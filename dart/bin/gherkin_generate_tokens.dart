import 'dart:io';

import 'package:gherkin/language.dart';
import 'package:gherkin/tokens.dart';

/// Emits the tokenized representation of one or more Gherkin feature files,
/// matching the `*.tokens` reference format used by the acceptance tests.
///
/// Mirrors the `gherkin-generate-tokens` binaries of the other first-party
/// implementations (Java, Go, Ruby).
void main(List<String> args) {
  final languages = loadGherkinLanguagesFromJsonAsset();
  final dialectProvider = GherkinDialectProvider(languages);

  for (final path in args) {
    final tokenMatcher =
        path.endsWith('.md')
            ? MarkdownTokenMatcher(dialectProvider)
            : TokenMatcher(dialectProvider);
    stdout.write(TokensGenerator.generateTokens(path, tokenMatcher));
  }
}
