import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/language/gherkin_language_constants.dart';
import 'package:cucumber_gherkin/src/language/gherkin_language_keywords.dart';
import 'package:cucumber_gherkin/src/language/gherkin_line.dart';
import 'package:cucumber_gherkin/src/language/location.dart';
import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/parser/token_matcher.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// The [TokenMatcher] for plain (`.feature`) Gherkin sources.
class GherkinTokenMatcher implements TokenMatcher {
  /// Creates a matcher over the given dialects map, defaulting to English
  /// (`en`) unless another default language is supplied.
  GherkinTokenMatcher(this._dialects, [this._defaultLanguage = 'en']) {
    _useLanguage(
      _defaultLanguage,
      _lookupKeywords(_dialects, _defaultLanguage),
    );
  }
  static final RegExp _languagePattern = RegExp(
    r'^\s*#\s*language\s*:\s*([a-zA-Z\-_]+)\s*$',
  );

  final Map<String, GherkinLanguageKeywords> _dialects;
  final String _defaultLanguage;
  final Map<String, messages.StepKeywordType> _keywordTypesMap =
      <String, messages.StepKeywordType>{};

  late String _currentLanguage;
  late GherkinLanguageKeywords _currentKeywords;
  late List<String> _stepKeywordsByLengthDesc;
  String _activeDocStringSeparator = '';
  int _indentToRemove = 0;

  @override
  void reset() {
    _activeDocStringSeparator = '';
    _indentToRemove = 0;
    _useLanguage(
      _defaultLanguage,
      _lookupKeywords(_dialects, _defaultLanguage),
    );
  }

  @override
  bool matchEof(Token token) {
    if (token.isEof) {
      _setTokenMatched(token, TokenType.eof);
      return true;
    }
    return false;
  }

  @override
  bool matchOther(Token token) {
    // Take the whole line, minus DocString indents.
    final text = token.line.getLineText(_indentToRemove);
    _setTokenMatched(
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
      _setTokenMatched(token, TokenType.empty);
      return true;
    }
    return false;
  }

  @override
  bool matchComment(Token token) {
    if (token.line.startsWith(commentPrefix)) {
      final text = token.line.getLineText();
      _setTokenMatched(token, TokenType.comment, text: text, indent: 0);
      return true;
    }
    return false;
  }

  @override
  bool matchLanguage(Token token) {
    final match = _languagePattern.firstMatch(token.line.getLineText());
    if (match != null) {
      final language = match.group(1) ?? '';
      _setTokenMatched(token, TokenType.language, text: language);
      _useLanguage(
        language,
        _lookupKeywords(_dialects, language, token.location),
      );
      return true;
    }
    return false;
  }

  @override
  bool matchTagLine(Token token) {
    if (token.line.startsWith(tagPrefix)) {
      _setTokenMatched(token, TokenType.tagLine, items: token.line.tags);
      return true;
    }
    return false;
  }

  @override
  bool matchFeatureLine(Token token) =>
      _matchTitleLine(token, TokenType.featureLine, _currentKeywords.feature);

  @override
  bool matchRuleLine(Token token) =>
      _matchTitleLine(token, TokenType.ruleLine, _currentKeywords.rule);

  @override
  bool matchBackgroundLine(Token token) => _matchTitleLine(
    token,
    TokenType.backgroundLine,
    _currentKeywords.background,
  );

  @override
  bool matchScenarioLine(Token token) =>
      _matchTitleLine(
        token,
        TokenType.scenarioLine,
        _currentKeywords.scenario,
      ) ||
      _matchTitleLine(
        token,
        TokenType.scenarioLine,
        _currentKeywords.scenarioOutline,
      );

  @override
  bool matchExamplesLine(Token token) =>
      _matchTitleLine(token, TokenType.examplesLine, _currentKeywords.examples);

  bool _matchTitleLine(
    Token token,
    TokenType tokenType,
    List<String> keywords,
  ) {
    for (final keyword in keywords) {
      if (token.line.startsWithTitleKeyword(keyword)) {
        final title = token.line.getRestTrimmed(
          keyword.length + titleKeywordSeparator.length,
        );
        _setTokenMatched(token, tokenType, keyword: keyword, text: title);
        return true;
      }
    }
    return false;
  }

  @override
  bool matchDocStringSeparator(Token token) =>
      _activeDocStringSeparator.isEmpty
          // open
          ? _matchDocStringSeparator(token, docStringSeparator, true) ||
              _matchDocStringSeparator(
                token,
                docStringAlternativeSeparator,
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
      _setTokenMatched(
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
    for (final keyword in _stepKeywordsByLengthDesc) {
      if (token.line.startsWith(keyword)) {
        final stepText = token.line.getRestTrimmed(keyword.length);
        _setTokenMatched(
          token,
          TokenType.stepLine,
          keyword: keyword,
          text: stepText,
          keywordType:
              _keywordTypesMap[keyword] ?? messages.StepKeywordType.unknown,
        );
        return true;
      }
    }
    return false;
  }

  @override
  bool matchTableRow(Token token) {
    if (token.line.startsWith(tableCellSeparator)) {
      _setTokenMatched(token, TokenType.tableRow, items: token.line.tableCells);
      return true;
    }
    return false;
  }

  /// Records that [token] matched [matchedType], populating its matched
  /// keyword, text, items, indentation, and location.
  void _setTokenMatched(
    Token token,
    TokenType matchedType, {
    String text = '',
    String keyword = '',
    messages.StepKeywordType? keywordType,
    int? indent,
    Iterable<GherkinLineSpan> items = const <GherkinLineSpan>[],
  }) {
    final matchedIndent =
        matchedType == TokenType.empty ? 0 : indent ?? token.line.indent;
    token
      ..matchedType = matchedType
      ..matchedKeyword = keyword
      ..matchedKeywordType = keywordType
      ..matchedText = text
      ..matchedItems = items
      ..location = Location(token.location.line, matchedIndent + 1);
    // Only Feature lines carry the active dialect into the AST builder.
    if (matchedType == TokenType.featureLine) {
      token.matchedLanguage = _currentLanguage;
    }
  }

  void _useLanguage(String language, GherkinLanguageKeywords keywords) {
    _currentLanguage = language;
    _currentKeywords = keywords;
    // Longest first so a short keyword that is a prefix of a longer one cannot
    // steal the match.
    _stepKeywordsByLengthDesc =
        <String>{
            ...keywords.given,
            ...keywords.when,
            ...keywords.then,
            ...keywords.and,
            ...keywords.but,
          }.toList()
          ..sort((a, b) => b.length - a.length);
    _initializeKeywordTypes(keywords);
  }

  String _unescapeDocString(String text) {
    if (docStringSeparator == _activeDocStringSeparator) {
      return text.replaceFirst(r'\"\"\"', docStringSeparator);
    }
    if (docStringAlternativeSeparator == _activeDocStringSeparator) {
      return text.replaceFirst(r'\`\`\`', docStringAlternativeSeparator);
    }
    return text;
  }

  void _initializeKeywordTypes(GherkinLanguageKeywords keywords) {
    _keywordTypesMap.clear();
    void mapKeywords(
      Iterable<String> stepKeywords,
      messages.StepKeywordType type,
    ) {
      for (final keyword in stepKeywords) {
        final existing = _keywordTypesMap[keyword];
        // Ambiguous keywords (e.g. `* ` in given/when/then/and) are unknown.
        _keywordTypesMap[keyword] =
            existing == null || existing == type
                ? type
                : messages.StepKeywordType.unknown;
      }
    }

    mapKeywords(keywords.given, messages.StepKeywordType.context);
    mapKeywords(keywords.when, messages.StepKeywordType.action);
    mapKeywords(keywords.then, messages.StepKeywordType.outcome);
    mapKeywords(keywords.and, messages.StepKeywordType.conjunction);
    mapKeywords(keywords.but, messages.StepKeywordType.conjunction);
  }

  static GherkinLanguageKeywords _lookupKeywords(
    Map<String, GherkinLanguageKeywords> dialects,
    String language, [
    Location location = Location.empty,
  ]) {
    final keywords = dialects[language];
    if (keywords == null) {
      throw NoSuchLanguageException(language, location);
    }
    return keywords;
  }
}
