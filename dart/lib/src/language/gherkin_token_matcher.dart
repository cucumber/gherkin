import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:gherkin/extensions.dart';
import 'package:gherkin/parser.dart';
import 'package:gherkin/src/language/gherkin_language_constants.dart';
import 'package:gherkin/src/language/gherkin_dialect.dart';
import 'package:gherkin/src/language/gherkin_dialect_provider.dart';
import 'package:gherkin/src/language/gherkin_line.dart';
import 'package:gherkin/src/language/gherkin_line_span.dart';
import 'package:gherkin/src/language/location.dart';
import 'package:gherkin/src/language/token.dart';
import 'package:gherkin/src/language/token_type.dart';

/// The [TokenMatcher] for plain (`.feature`) Gherkin sources.
class GherkinTokenMatcher implements TokenMatcher {
  /// Creates a matcher that resolves dialects through [_dialectProvider].
  GherkinTokenMatcher(this._dialectProvider)
    : _currentDialect = _dialectProvider.defaultDialect {
    _initializeKeywordTypes();
  }
  static final RegExp _languagePattern = RegExp(
    r'^\s*#\s*language\s*:\s*([a-zA-Z\-_]+)\s*$',
  );

  final GherkinDialectProvider _dialectProvider;

  GherkinDialect _currentDialect;
  String _activeDocStringSeparator = Strings.empty;
  int _indentToRemove = 0;
  Map<String, List<messages.StepKeywordType>> _keywordTypesMap = {};

  /// The dialect currently in effect.
  GherkinDialect get currentDialect => _currentDialect;

  @override
  void reset() {
    _activeDocStringSeparator = Strings.empty;
    _indentToRemove = 0;
    _currentDialect = _dialectProvider.defaultDialect;
    _initializeKeywordTypes();
  }

  @override
  bool matchEof(Token token) {
    if (token.isEof) {
      setTokenMatched(token, TokenType.eof);
      return true;
    }
    return false;
  }

  @override
  bool matchOther(Token token) {
    /// take the entire line, except removing DocString indents
    final text = token.line.getLineText(_indentToRemove);
    setTokenMatched(
      token,
      TokenType.other,
      text: _unescapeDocString(text),
      indent: 0,
    );
    return true;
  }

  @override
  bool matchEmpty(Token token) {
    if (token.line.isEmptyLine) {
      setTokenMatched(token, TokenType.empty);
      return true;
    }
    return false;
  }

  @override
  bool matchComment(Token token) {
    if (token.line.startsWith(GherkinLanguageConstants.commentPrefix)) {
      final text = token.line.getLineText(GherkinLine.entireLine);
      setTokenMatched(token, TokenType.comment, text: text, indent: 0);
      return true;
    }
    return false;
  }

  @override
  bool matchLanguage(Token token) {
    final match = _languagePattern.firstMatch(
      token.line.getLineText(GherkinLine.entireLine),
    );
    if (match != null) {
      final language = match.group(1) ?? Strings.empty;
      setTokenMatched(token, TokenType.language, text: language);
      _currentDialect = _dialectProvider.getDialect(language, token.location);
      _initializeKeywordTypes();
      return true;
    }
    return false;
  }

  @override
  bool matchTagLine(Token token) {
    if (token.line.startsWith(GherkinLanguageConstants.tagPrefix)) {
      setTokenMatched(token, TokenType.tagLine, items: token.line.tags);
      return true;
    }
    return false;
  }

  @override
  bool matchFeatureLine(Token token) => _matchTitleLine(
    token,
    TokenType.featureLine,
    currentDialect.featureKeywords,
  );

  @override
  bool matchRuleLine(Token token) =>
      _matchTitleLine(token, TokenType.ruleLine, currentDialect.ruleKeywords);

  @override
  bool matchBackgroundLine(Token token) => _matchTitleLine(
    token,
    TokenType.backgroundLine,
    currentDialect.backgroundKeywords,
  );

  @override
  bool matchScenarioLine(Token token) =>
      _matchTitleLine(
        token,
        TokenType.scenarioLine,
        currentDialect.scenarioKeywords,
      ) ||
      _matchTitleLine(
        token,
        TokenType.scenarioLine,
        currentDialect.scenarioOutlineKeywords,
      );

  @override
  bool matchExamplesLine(Token token) => _matchTitleLine(
    token,
    TokenType.examplesLine,
    currentDialect.examplesKeywords,
  );

  bool _matchTitleLine(
    Token token,
    TokenType tokenType,
    List<String> keywords,
  ) {
    for (final keyword in keywords) {
      if (token.line.startsWithTitleKeyword(keyword)) {
        final title = token.line.getRestTrimmed(
          keyword.length +
              GherkinLanguageConstants.titleKeywordSeparator.length,
        );
        setTokenMatched(token, tokenType, keyword: keyword, text: title);
        return true;
      }
    }
    return false;
  }

  @override
  bool matchDocStringSeparator(Token token) =>
      _activeDocStringSeparator.isEmpty
          // open
          ? _matchDocStringSeparator(
                token,
                GherkinLanguageConstants.docStringSeparator,
                true,
              ) ||
              _matchDocStringSeparator(
                token,
                GherkinLanguageConstants.docStringAlternativeSeparator,
                true,
              )
          // close
          : _matchDocStringSeparator(token, _activeDocStringSeparator, false);

  bool _matchDocStringSeparator(Token token, String separator, bool isOpen) {
    if (token.line.startsWith(separator)) {
      var mediaType = Strings.empty;
      if (isOpen) {
        mediaType = token.line.getRestTrimmed(separator.length);
        _activeDocStringSeparator = separator;
        _indentToRemove = token.line.indent;
      } else {
        _activeDocStringSeparator = Strings.empty;
        _indentToRemove = 0;
      }
      setTokenMatched(
        token,
        TokenType.docStringSeparator,
        text: mediaType,
        keyword: separator,
      );
      return true;
    }
    return false;
  }

  @override
  bool matchStepLine(Token token) {
    final keywords =
        currentDialect.stepKeywords.toList()
          ..sort((a, b) => b.length - a.length);
    for (final keyword in keywords) {
      if (token.line.startsWith(keyword)) {
        final stepText = token.line.getRestTrimmed(keyword.length);
        setTokenMatched(
          token,
          TokenType.stepLine,
          keyword: keyword,
          text: stepText,
          keywordType: _keywordType(keyword),
        );
        return true;
      }
    }
    return false;
  }

  @override
  bool matchTableRow(Token token) {
    if (token.line.startsWith(GherkinLanguageConstants.tableCellSeparator)) {
      setTokenMatched(token, TokenType.tableRow, items: token.line.tableCells);
      return true;
    }
    return false;
  }

  /// Records that [token] matched [matchedType], populating its matched
  /// keyword, text, items, indentation, and location.
  void setTokenMatched(
    Token token,
    TokenType matchedType, {
    String text = Strings.empty,
    String keyword = Strings.empty,
    messages.StepKeywordType? keywordType,
    int indent = Int.min,
    Iterable<GherkinLineSpan> items = const <GherkinLineSpan>[],
  }) {
    token
      ..matchedType = matchedType
      ..matchedKeyword = keyword
      ..matchedKeywordType = keywordType
      ..matchedText = text
      ..matchedItems = items
      ..matchedGherkinDialect = currentDialect
      ..matchedIndent =
          matchedType == TokenType.empty
              ? 0
              : indent.isNotMin
              ? indent
              : token.line.indent
      ..location = Location(token.location.line, token.matchedIndent + 1);
  }

  void _initializeKeywordTypes() {
    _keywordTypesMap = {};
    _addKeywordTypeMappings(
      currentDialect.givenStepKeywords,
      messages.StepKeywordType.context,
    );
    _addKeywordTypeMappings(
      currentDialect.whenStepKeywords,
      messages.StepKeywordType.action,
    );
    _addKeywordTypeMappings(
      currentDialect.thenStepKeywords,
      messages.StepKeywordType.outcome,
    );
    _addKeywordTypeMappings(
      currentDialect.andStepKeywords,
      messages.StepKeywordType.conjunction,
    );
    _addKeywordTypeMappings(
      currentDialect.butStepKeywords,
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

  messages.StepKeywordType _keywordType(String keyword) {
    final keywordTypes = _keywordTypesMap[keyword];
    if (keywordTypes == null || keywordTypes.length != 1) {
      return messages.StepKeywordType.unknown;
    }
    return keywordTypes.single;
  }

  String _unescapeDocString(String text) {
    if (GherkinLanguageConstants.docStringSeparator ==
        _activeDocStringSeparator) {
      return text.replaceFirst(
        r'\"\"\"',
        GherkinLanguageConstants.docStringSeparator,
      );
    }
    if (GherkinLanguageConstants.docStringAlternativeSeparator ==
        _activeDocStringSeparator) {
      return text.replaceFirst(
        r'\`\`\`',
        GherkinLanguageConstants.docStringAlternativeSeparator,
      );
    }
    return text;
  }
}
