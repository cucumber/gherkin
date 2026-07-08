import 'dart:io';

import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:cucumber_gherkin/src/language/gherkin_dialect_provider.dart';
import 'package:cucumber_gherkin/src/language/gherkin_token_matcher.dart';

import '../tool/tokens_generator.dart';

/// Emits the tokenized representation of one or more Gherkin feature files,
/// matching the `*.tokens` format used by the acceptance tests.
void main(List<String> args) {
  const languages = builtinDialects;
  final dialectProvider = GherkinDialectProvider(languages);

  for (final path in args) {
    stdout.write(
      TokensGenerator.generateTokens(
        path,
        GherkinTokenMatcher(dialectProvider),
      ),
    );
  }
}
