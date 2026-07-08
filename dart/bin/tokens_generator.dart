import 'dart:io';

import 'package:cucumber_gherkin/src/language/string_token_scanner.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/parser/token_matcher.dart';

import 'token_formatter_builder.dart';

/// Generates the shared `*.tokens` text representation of a feature file,
/// used by the acceptance tests.
class TokensGenerator {
  /// Scans the file at [featureFilePath] with [tokenMatcher] and returns its
  /// `*.tokens` text.
  static String generateTokens(
    String featureFilePath,
    TokenMatcher tokenMatcher,
  ) {
    final tokenFormatterBuilder = TokenFormatterBuilder();
    final parser = Parser<Object?>(tokenFormatterBuilder);
    final tokenScanner = StringTokenScanner(
      File(featureFilePath).readAsStringSync(),
    );
    parser.parse(tokenScanner, tokenMatcher);
    return tokenFormatterBuilder.tokensText;
  }
}
