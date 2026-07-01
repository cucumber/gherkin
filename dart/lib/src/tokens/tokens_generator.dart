import 'package:cucumber_gherkin/src/helpers/line_ending_helper.dart';
import 'package:cucumber_gherkin/src/language/file_token_scanner.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/parser/token_matcher.dart';
import 'package:cucumber_gherkin/src/tokens/no_op_result.dart';
import 'package:cucumber_gherkin/src/tokens/token_formatter_builder.dart';

/// Generates the shared `*.tokens` text representation of a feature file,
/// used by the acceptance tests.
class TokensGenerator {
  /// Scans the file at [featureFilePath] with [tokenMatcher] and returns its
  /// normalized `*.tokens` text.
  static String generateTokens(
    String featureFilePath,
    TokenMatcher tokenMatcher,
  ) {
    final tokenFormatterBuilder = TokenFormatterBuilder();
    final parser = Parser<NoOpResult>(tokenFormatterBuilder);
    final tokenScanner = FileTokenScanner.fromPath(featureFilePath);
    parser.parse(tokenScanner, tokenMatcher);
    final tokensText = tokenFormatterBuilder.getTokensText();
    return LineEndingHelper.normalizeLineEndings(tokensText);
  }
}
