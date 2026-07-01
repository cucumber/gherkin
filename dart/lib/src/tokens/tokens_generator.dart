import 'package:gherkin/helpers.dart';
import 'package:gherkin/language.dart';
import 'package:gherkin/parser.dart';
import 'package:gherkin/src/tokens/no_op_result.dart';
import 'package:gherkin/src/tokens/token_formatter_builder.dart';

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
