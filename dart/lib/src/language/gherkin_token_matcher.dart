import 'package:cucumber_gherkin/src/language/gherkin_dialect.dart';
import 'package:cucumber_gherkin/src/language/gherkin_dialect_provider.dart';
import 'package:cucumber_gherkin/src/language/gherkin_language_constants.dart';
import 'package:cucumber_gherkin/src/language/gherkin_line_span.dart';
import 'package:cucumber_gherkin/src/language/location.dart';
import 'package:cucumber_gherkin/src/language/step_keyword_types.dart';
import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/language/token_type.dart';
import 'package:cucumber_gherkin/src/parser/token_matcher.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// The [TokenMatcher] for plain (`.feature`) Gherkin sources.
class GherkinTokenMatcher with StepKeywordTypes implements TokenMatcher {
  /// Creates a matcher that resolves dialects through [_dialectProvider].
  GherkinTokenMatcher(this._dialectProvider)
    : _currentDialect = _dialectProvider.defaultDialect {
    initializeKeywordTypes(_currentDialect);
  }
  static final RegExp _languagePattern = RegExp(
    r'^\s*#\s*language\s*:\s*([a-zA-Z\-_]+)\s*$',
  );

  final GherkinDialectProvider _dialectProvider;

  GherkinDialect _currentDialect;
  String _activeDocStringSeparator = '';
  int _indentToRemove = 0;

  /// The dialect currently in effect.
  GherkinDialect get currentDialect => _currentDialect;

  @override
  void reset() {
    _activeDocStringSeparator = '';
    _indentToRemove = 0;
    _currentDialect = _dialectProvider.defaultDialect;
    initializeKeywordTypes(_currentDialect);
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
    // Take the whole line, minus DocString indents.
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
      final text = token.line.getLineText();
      setTokenMatched(token, TokenType.comment, text: text, indent: 0);
      return true;
    }
    return false;
  }

  @override
  bool matchLanguage(Token token) {
    final match = _languagePattern.firstMatch(
      token.line.getLineText(),
    );
    if (match != null) {
      final language = match.group(1) ?? '';
      setTokenMatched(token, TokenType.language, text: language);
      _currentDialect = _dialectProvider.getDialect(language, token.location);
      initializeKeywordTypes(_currentDialect);
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
      var mediaType = '';
      if (isOpen) {
        mediaType = token.line.getRestTrimmed(separator.length);
        _activeDocStringSeparator = separator;
        _indentToRemove = token.line.indent;
      } else {
        _activeDocStringSeparator = '';
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
    final keywords = currentDialect.stepKeywordsByLengthDesc;
    for (final keyword in keywords) {
      if (token.line.startsWith(keyword)) {
        final stepText = token.line.getRestTrimmed(keyword.length);
        setTokenMatched(
          token,
          TokenType.stepLine,
          keyword: keyword,
          text: stepText,
          // The plain matcher reports `unknown` for an unmapped keyword, unlike
          // the Markdown matcher which reports `null`.
          keywordType:
              keywordTypeOrNull(keyword) ?? messages.StepKeywordType.unknown,
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
      ..matchedGherkinDialect = currentDialect
      ..matchedIndent =
          matchedType == TokenType.empty ? 0 : indent ?? token.line.indent
      ..location = Location(token.location.line, token.matchedIndent + 1);
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
