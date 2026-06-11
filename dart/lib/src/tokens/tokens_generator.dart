import 'package:gherkin/helpers.dart';
import 'package:gherkin/language.dart';
import 'package:gherkin/parser.dart';
import 'token_formatter_builder.dart';
import 'no_op_result.dart';

class TokensGenerator {
  static String generateTokens(
    String featureFilePath,
    ITokenMatcher tokenMatcher,
  ) {
    var tokenFormatterBuilder = TokenFormatterBuilder();
    var parser = Parser<NoOpResult>(tokenFormatterBuilder);
    var tokenScanner = FileTokenScanner.fromPath(featureFilePath);
    parser.parse(tokenScanner, tokenMatcher);
    var tokensText = tokenFormatterBuilder.getTokensText();
    return LineEndingHelper.normalizeLineEndings(tokensText);
  }
}
