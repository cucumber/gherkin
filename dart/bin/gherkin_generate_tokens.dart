import 'dart:io';

import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:cucumber_gherkin/src/language/gherkin_token_matcher.dart';
import 'package:cucumber_gherkin/src/language/string_token_scanner.dart';
import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/builder.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';

/// Acceptance CLI: feature paths → `*.tokens` text on stdout.
void main(List<String> args) {
  final matcher = GherkinTokenMatcher(builtinDialects);

  for (final path in args) {
    final builder = _TokenFormatterBuilder();
    Parser<void>(
      builder,
    ).parse(StringTokenScanner(File(path).readAsStringSync()), matcher);
    stdout.write(builder.tokensText);
  }
}

class _TokenFormatterBuilder implements Builder<void> {
  final StringBuffer _buffer = StringBuffer();

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

/// Maps [TokenType] enum names to the PascalCase labels in `*.tokens` fixtures.
String _wireName(TokenType tokenType) {
  final name = tokenType.name;
  if (name == 'eof') {
    return 'EOF';
  }
  return '${name[0].toUpperCase()}${name.substring(1)}';
}
