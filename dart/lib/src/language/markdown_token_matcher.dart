import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:cucumber_gherkin/exceptions.dart';
import 'package:cucumber_gherkin/src/language/gherkin_dialect.dart';
import 'package:cucumber_gherkin/src/language/gherkin_dialect_provider.dart';
import 'package:cucumber_gherkin/src/language/gherkin_line_span.dart';
import 'package:cucumber_gherkin/src/language/location.dart';
import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/language/token_type.dart';
import 'package:cucumber_gherkin/src/parser/token_matcher.dart';

/// The [TokenMatcher] for Markdown (`.feature.md`) Gherkin sources.
class MarkdownTokenMatcher implements TokenMatcher {
  /// Creates a matcher that resolves dialects through [_dialectProvider],
  /// defaulting to [_defaultDialectName] when no `# language:` header is found.
  MarkdownTokenMatcher(
    this._dialectProvider, [
    this._defaultDialectName = 'en',
  ]) {
    _currentDialect = _dialectProvider.getDialect(
      _defaultDialectName,
      Location.empty,
    );
    _initializeDialectState();
  }
  final GherkinDialectProvider _dialectProvider;
  final String _defaultDialectName;

  late GherkinDialect _currentDialect;
  late List<String> _nonStarStepKeywords;
  late List<String> _headerKeywords;
  late Map<String, List<messages.StepKeywordType>> _keywordTypesMap;

  RegExp _activeDocStringSeparator = RegExp('^(```[`]*)(.*)');
  int _indentToRemove = 0;
  bool _matchedFeatureLine = false;

  @override
  void reset() {
    _currentDialect = _dialectProvider.getDialect(
      _defaultDialectName,
      Location.empty,
    );
    _activeDocStringSeparator = RegExp('^(```[`]*)(.*)');
    _indentToRemove = 0;
    _matchedFeatureLine = false;
    _initializeDialectState();
  }

  @override
  bool matchLanguage(Token token) => false;

  @override
  bool matchEmpty(Token token) {
    var result = token.line.isEmptyLine;
    if (!result && _isGfmTableSeparator(token.line.tableCells.toList())) {
      result = true;
    }
    if (!matchTagLine(token) &&
        !matchFeatureLine(token) &&
        !matchScenarioLine(token) &&
        !matchBackgroundLine(token) &&
        !matchExamplesLine(token) &&
        !matchRuleLine(token) &&
        !matchTableRow(token) &&
        !matchComment(token) &&
        !matchDocStringSeparator(token) &&
        !matchEof(token) &&
        !matchStepLine(token)) {
      result = true;
    }
    if (result) {
      _setTokenMatched(token, TokenType.empty);
    }
    return result;
  }

  @override
  bool matchOther(Token token) {
    _setTokenMatched(
      token,
      TokenType.other,
      text: token.line.getLineText(_indentToRemove),
      indent: 0,
    );
    return true;
  }

  @override
  bool matchComment(Token token) {
    if (!token.line.startsWith('|')) {
      return false;
    }
    final tableCells = token.line.tableCells.toList();
    final result = _isGfmTableSeparator(tableCells);
    if (result) {
      _setTokenMatched(token, TokenType.empty, indent: 0);
    }
    return result;
  }

  @override
  bool matchDocStringSeparator(Token token) {
    final match = _activeDocStringSeparator.firstMatch(
      token.line.getLineText(-1),
    );
    if (match == null) {
      return false;
    }

    final separator = match.group(1) ?? '';
    final mediaType = match.groupCount >= 2 ? match.group(2) ?? '' : '';
    if (_activeDocStringSeparator.pattern == '^(```[`]*)(.*)') {
      _activeDocStringSeparator = RegExp('^(${RegExp.escape(separator)})\$');
      _indentToRemove = token.line.indent;
    } else {
      _activeDocStringSeparator = RegExp('^(```[`]*)(.*)');
      _indentToRemove = 0;
    }

    _setTokenMatched(
      token,
      TokenType.docStringSeparator,
      keyword: separator,
      text: mediaType.trim(),
    );
    return true;
  }

  @override
  bool matchEof(Token token) {
    if (!token.isEof) {
      return false;
    }
    _setTokenMatched(token, TokenType.eof);
    return true;
  }

  @override
  bool matchFeatureLine(Token token) {
    if (_matchedFeatureLine) {
      return false;
    }

    var result = _matchTitleLine(
      token,
      _headerPrefix,
      _currentDialect.featureKeywords,
      ':',
      TokenType.featureLine,
    );
    if (!result) {
      _setTokenMatched(
        token,
        TokenType.featureLine,
        text: token.line.getLineText(-1),
      );
      result = true;
    }
    _matchedFeatureLine = result;
    return result;
  }

  @override
  bool matchBackgroundLine(Token token) => _matchTitleLine(
    token,
    _headerPrefix,
    _currentDialect.backgroundKeywords,
    ':',
    TokenType.backgroundLine,
  );

  @override
  bool matchRuleLine(Token token) => _matchTitleLine(
    token,
    _headerPrefix,
    _currentDialect.ruleKeywords,
    ':',
    TokenType.ruleLine,
  );

  @override
  bool matchScenarioLine(Token token) =>
      _matchTitleLine(
        token,
        _headerPrefix,
        _currentDialect.scenarioKeywords,
        ':',
        TokenType.scenarioLine,
      ) ||
      _matchTitleLine(
        token,
        _headerPrefix,
        _currentDialect.scenarioOutlineKeywords,
        ':',
        TokenType.scenarioLine,
      );

  @override
  bool matchExamplesLine(Token token) => _matchTitleLine(
    token,
    _headerPrefix,
    _currentDialect.examplesKeywords,
    ':',
    TokenType.examplesLine,
  );

  @override
  bool matchStepLine(Token token) => _matchTitleLine(
    token,
    _bulletPrefix,
    _nonStarStepKeywords,
    '',
    TokenType.stepLine,
  );

  @override
  bool matchTableRow(Token token) {
    final lineText = token.line.getLineText(0);
    if (!RegExp(r'^\s{2,5}\|').hasMatch(lineText)) {
      return false;
    }
    final tableCells = token.line.tableCells.toList();
    if (_isGfmTableSeparator(tableCells)) {
      return false;
    }
    _setTokenMatched(
      token,
      TokenType.tableRow,
      keyword: '|',
      items: tableCells,
    );
    return true;
  }

  @override
  bool matchTagLine(Token token) {
    final tags = <GherkinLineSpan>[];
    final trimmed = token.line.getLineText(-1);
    final re = RegExp('`(@[^`]+)`');
    for (final match in re.allMatches(trimmed)) {
      tags.add(
        GherkinLineSpan(
          token.line.indent + match.start + 2,
          match.group(1) ?? '',
        ),
      );
    }
    if (tags.isEmpty) {
      return false;
    }
    _setTokenMatched(token, TokenType.tagLine, items: tags);
    return true;
  }

  bool _matchTitleLine(
    Token token,
    String prefix,
    List<String> keywords,
    String suffix,
    TokenType matchedType,
  ) {
    final escapedKeywords = keywords.map(RegExp.escape).join('|');
    final regexp = RegExp(
      '$prefix($escapedKeywords)${RegExp.escape(suffix)}(.*)',
    );
    final match = regexp.firstMatch(token.line.getLineText(0));
    if (match == null) {
      return false;
    }

    final prefixText = match.group(1) ?? '';
    final keyword = match.group(2) ?? '';
    final text = match.group(3)?.trim() ?? '';
    final keywordType = _keywordType(keyword);
    _setTokenMatched(
      token,
      matchedType,
      keyword: keyword,
      keywordType: keywordType,
      text: text,
      indent: prefixText.length,
    );
    return true;
  }

  void _setTokenMatched(
    Token token,
    TokenType matchedType, {
    String text = '',
    String keyword = '',
    messages.StepKeywordType? keywordType,
    int? indent,
    Iterable<GherkinLineSpan> items = const <GherkinLineSpan>[],
  }) {
    token
      ..matchedType = matchedType
      ..matchedKeyword = keyword
      ..matchedKeywordType = keywordType
      ..matchedText = text
      ..matchedItems = items
      ..matchedGherkinDialect = _currentDialect
      ..matchedIndent =
          matchedType == TokenType.empty ? 0 : indent ?? token.line.indent
      ..location = Location(token.location.line, token.matchedIndent + 1);
  }

  void _initializeDialectState() {
    _nonStarStepKeywords =
        <String>{
            ..._currentDialect.givenStepKeywords,
            ..._currentDialect.whenStepKeywords,
            ..._currentDialect.thenStepKeywords,
            ..._currentDialect.andStepKeywords,
            ..._currentDialect.butStepKeywords,
          }.where((keyword) => keyword != '* ').toList()
          ..sort((a, b) => b.length - a.length);

    _headerKeywords =
        <String>{
          ..._currentDialect.featureKeywords,
          ..._currentDialect.backgroundKeywords,
          ..._currentDialect.ruleKeywords,
          ..._currentDialect.scenarioOutlineKeywords,
          ..._currentDialect.scenarioKeywords,
          ..._currentDialect.examplesKeywords,
        }.toList();

    if (_headerKeywords.isEmpty) {
      throw NoSuchLanguageException(_defaultDialectName);
    }

    _keywordTypesMap = {};
    _addKeywordTypeMappings(
      _currentDialect.givenStepKeywords,
      messages.StepKeywordType.context,
    );
    _addKeywordTypeMappings(
      _currentDialect.whenStepKeywords,
      messages.StepKeywordType.action,
    );
    _addKeywordTypeMappings(
      _currentDialect.thenStepKeywords,
      messages.StepKeywordType.outcome,
    );
    _addKeywordTypeMappings(
      _currentDialect.andStepKeywords,
      messages.StepKeywordType.conjunction,
    );
    _addKeywordTypeMappings(
      _currentDialect.butStepKeywords,
      messages.StepKeywordType.conjunction,
    );
  }

  void _addKeywordTypeMappings(
    Iterable<String> keywords,
    messages.StepKeywordType keywordType,
  ) {
    for (final keyword in keywords) {
      _keywordTypesMap
          .putIfAbsent(keyword, () => <messages.StepKeywordType>[])
          .add(keywordType);
    }
  }

  messages.StepKeywordType? _keywordType(String keyword) {
    final keywordTypes = _keywordTypesMap[keyword];
    if (keywordTypes == null) {
      return null;
    }
    if (keywordTypes.length != 1) {
      return messages.StepKeywordType.unknown;
    }
    return keywordTypes.single;
  }

  bool _isGfmTableSeparator(List<GherkinLineSpan> tableCells) {
    return tableCells.any((cell) => RegExp(r'^:?-+:?$').hasMatch(cell.text));
  }

  static const _bulletPrefix = r'^(\s*[*+-]\s*)';
  static const _headerPrefix = r'^(#{1,6}\s)';
}
