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
    // Emit a trailing newline so the final `EOF` line is newline-terminated,
    // matching the reference implementations (e.g. Go uses `Fprintln` for
    // every token, including EOF). `generateTokens` trims trailing newlines
    // during normalization, so re-add one here via `writeln`.
    stdout.writeln(TokensGenerator.generateTokens(path, tokenMatcher));
  }
}
