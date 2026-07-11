import 'dart:io';

import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:cucumber_gherkin/src/language/gherkin_dialect_provider.dart';
import 'package:cucumber_gherkin/src/language/gherkin_token_matcher.dart';
import 'package:cucumber_gherkin/src/language/string_token_scanner.dart';
import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/builder.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';

/// Emits the tokenized representation of one or more Gherkin feature files,
/// matching the `*.tokens` format used by the acceptance tests.
///
/// This format is an acceptance-test artifact rather than part of the published
/// library, so the rendering lives here in the executable instead of `lib/`.
void main(List<String> args) {
  final matcher = GherkinTokenMatcher(GherkinDialectProvider(builtinDialects));

  for (final path in args) {
    final builder = _TokenFormatterBuilder();
    Parser<void>(
      builder,
    ).parse(StringTokenScanner(File(path).readAsStringSync()), matcher);
    stdout.write(builder.tokensText);
  }
}

/// A [Builder] that renders each scanned token in the `*.tokens` text format.
///
/// The output is produced as a side effect (accumulated in [tokensText]); the
/// parser's builder result is unused, hence `Builder<void>`.
class _TokenFormatterBuilder implements Builder<void> {
  final StringBuffer _buffer = StringBuffer();

  /// The full rendered token text accumulated so far.
  String get tokensText => _buffer.toString();

  @override
  void build(Token token) => _buffer.writeln(_formatToken(token));

  @override
  void endRule(RuleType ruleType) {}

  @override
  void startRule(RuleType ruleType) {}

  @override
  void reset() {}

  @override
  void get result {}
}

/// Returns the single-line `*.tokens` representation of [token].
String _formatToken(Token token) {
  if (token.isEof) {
    return 'EOF';
  }
  final matchedItems = token.matchedItems
      .map((element) => '${element.column}:${element.text}')
      .join(',');
  final matchedType = _wireName(token.matchedType);
  final matchedKeyword = token.matchedKeyword;
  final matchedKeywordType =
      matchedKeyword.isEmpty
          ? ''
          : token.matchedKeywordType == null
          ? '()'
          : '(${token.matchedKeywordType!.value})';
  return '(${token.location.line}:${token.location.column})'
      '$matchedType:$matchedKeywordType$matchedKeyword/${token.matchedText}/$matchedItems';
}

String _wireName(TokenType tokenType) {
  switch (tokenType) {
    case TokenType.none:
      return 'None';
    case TokenType.eof:
      return 'EOF';
    case TokenType.empty:
      return 'Empty';
    case TokenType.comment:
      return 'Comment';
    case TokenType.tagLine:
      return 'TagLine';
    case TokenType.featureLine:
      return 'FeatureLine';
    case TokenType.ruleLine:
      return 'RuleLine';
    case TokenType.backgroundLine:
      return 'BackgroundLine';
    case TokenType.scenarioLine:
      return 'ScenarioLine';
    case TokenType.examplesLine:
      return 'ExamplesLine';
    case TokenType.stepLine:
      return 'StepLine';
    case TokenType.docStringSeparator:
      return 'DocStringSeparator';
    case TokenType.tableRow:
      return 'TableRow';
    case TokenType.language:
      return 'Language';
    case TokenType.other:
      return 'Other';
  }
}
