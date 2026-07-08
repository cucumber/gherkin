import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/parser/token_matcher.dart';

import 'file_token_scanner.dart';
import 'no_op_result.dart';
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
    final parser = Parser<NoOpResult>(tokenFormatterBuilder);
    final tokenScanner = FileTokenScanner.fromPath(featureFilePath);
    parser.parse(tokenScanner, tokenMatcher);
    return tokenFormatterBuilder.tokensText;
  }
}
