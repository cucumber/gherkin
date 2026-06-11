import 'dart:collection';
import 'package:gherkin/exceptions.dart';
import 'package:gherkin/language.dart';

import 'package:gherkin/src/parser/i_builder.dart';
import 'package:gherkin/src/parser/i_token_matcher.dart';
import 'package:gherkin/src/parser/i_token_scanner.dart';
import 'package:gherkin/src/parser/parser_context.dart';
import 'package:gherkin/src/parser/rule_type.dart';

/// A recursive-descent Gherkin parser driven by a generated state machine.
///
/// The parser reads [Token]s from an [ITokenScanner], classifies them with an
/// [ITokenMatcher], and feeds the recognized grammar rules to an [IBuilder] of
/// type [T], which assembles the final result returned by [parse].
class Parser<T> {
  /// Creates a parser that emits its result through the given [IBuilder].
  Parser(this._builder);
  final IBuilder<T> _builder;
  bool _descriptionOpen = false;

  /// Whether parsing should throw on the first error instead of collecting
  /// every error encountered while scanning the document.
  bool stopAtFirstError = false;

  /// Parses the tokens produced by [tokenScanner], using [tokenMatcher] to
  /// classify each token, and returns the assembled result of type [T].
  ///
  /// Throws a [CompositeParserException] if one or more parse errors are
  /// encountered.
  T parse(ITokenScanner tokenScanner, ITokenMatcher tokenMatcher) {
    _descriptionOpen = false;
    _builder.reset();
    tokenMatcher.reset();

    final context = ParserContext(
      tokenScanner,
      tokenMatcher,
      Queue<Token>(),
      <ParserException>[],
    );

    _startRule(context, RuleType.gherkinDocument);
    var state = 0;
    Token token;
    do {
      token = _readToken(context);
      state = _matchToken(state, token, context);
    } while (!token.isEof);

    _endRule(context, RuleType.gherkinDocument);

    if (context.errors.isNotEmpty) {
      throw CompositeParserException(context.errors);
    }

    return _builder.result;
  }

  void _addError(ParserContext context, ParserException error) {
    // Deduplicate by (message, line, column) so the same parse-error at the
    // same location is not reported twice, but distinct errors with an
    // identical message at different locations are kept.
    for (final e in context.errors) {
      if (e.message == error.message &&
          e.location.line == error.location.line &&
          e.location.column == error.location.column) {
        return;
      }
    }
    context.errors.add(error);
    if (context.errors.length > 10) {
      throw CompositeParserException(context.errors);
    }
  }

  void _handleAstError<V>(ParserContext context, V Function() action) =>
      _handleExternalError(context, () {
        action();
      }, null);

  V _handleExternalError<V>(
    ParserContext context,
    V Function() action,
    V defaultValue,
  ) {
    if (stopAtFirstError) {
      return action();
    }

    try {
      return action();
    } on CompositeParserException catch (compositeParserException) {
      for (final error in compositeParserException.errors) {
        _addError(context, error);
      }
    } on ParserException catch (error) {
      _addError(context, error);
    }
    return defaultValue;
  }

  void _build(ParserContext context, Token token) =>
      _handleAstError(context, () => _builder.build(token));

  void _startRule(ParserContext context, RuleType ruleType) =>
      _handleAstError(context, () {
        _builder.startRule(ruleType);
        if (ruleType == RuleType.description) {
          _descriptionOpen = true;
        }
      });

  void _endRule(ParserContext context, RuleType ruleType) =>
      _handleAstError(context, () {
        _builder.endRule(ruleType);
        if (ruleType == RuleType.description) {
          _descriptionOpen = false;
        }
      });

  void _startDescriptionIfNeeded(ParserContext context) {
    if (!_descriptionOpen) {
      _startRule(context, RuleType.description);
    }
  }

  void _endDescriptionIfNeeded(ParserContext context) {
    if (_descriptionOpen) {
      _endRule(context, RuleType.description);
    }
  }

  Token _readToken(ParserContext context) =>
      context.tokenQueue.isNotEmpty
          ? context.tokenQueue.removeFirst()
          : context.tokenScanner.read();

  bool _matchEof(ParserContext context, Token token) {
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchEof(token),
      false,
    );
  }

  bool _matchEmpty(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchEmpty(token),
      false,
    );
  }

  bool _matchComment(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchComment(token),
      false,
    );
  }

  bool _matchTagLine(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchTagLine(token),
      false,
    );
  }

  bool _matchFeatureLine(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchFeatureLine(token),
      false,
    );
  }

  bool _matchRuleLine(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchRuleLine(token),
      false,
    );
  }

  bool _matchBackgroundLine(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchBackgroundLine(token),
      false,
    );
  }

  bool _matchScenarioLine(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchScenarioLine(token),
      false,
    );
  }

  bool _matchExamplesLine(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchExamplesLine(token),
      false,
    );
  }

  bool _matchStepLine(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchStepLine(token),
      false,
    );
  }

  bool _matchDocStringSeparator(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchDocStringSeparator(token),
      false,
    );
  }

  bool _matchTableRow(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchTableRow(token),
      false,
    );
  }

  bool _matchLanguage(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchLanguage(token),
      false,
    );
  }

  bool _matchOther(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchOther(token),
      false,
    );
  }

  int _matchToken(int state, Token token, ParserContext context) {
    int newState;
    switch (state) {
      case 0:
        newState = _matchTokenAt_0(token, context);
      case 1:
        newState = _matchTokenAt_1(token, context);
      case 2:
        newState = _matchTokenAt_2(token, context);
      case 3:
        newState = _matchTokenAt_3(token, context);
      case 4:
        newState = _matchTokenAt_4(token, context);
      case 5:
        newState = _matchTokenAt_5(token, context);
      case 6:
        newState = _matchTokenAt_6(token, context);
      case 7:
        newState = _matchTokenAt_7(token, context);
      case 8:
        newState = _matchTokenAt_8(token, context);
      case 9:
        newState = _matchTokenAt_9(token, context);
      case 10:
        newState = _matchTokenAt_10(token, context);
      case 11:
        newState = _matchTokenAt_11(token, context);
      case 12:
        newState = _matchTokenAt_12(token, context);
      case 13:
        newState = _matchTokenAt_13(token, context);
      case 14:
        newState = _matchTokenAt_14(token, context);
      case 15:
        newState = _matchTokenAt_15(token, context);
      case 16:
        newState = _matchTokenAt_16(token, context);
      case 17:
        newState = _matchTokenAt_17(token, context);
      case 18:
        newState = _matchTokenAt_18(token, context);
      case 19:
        newState = _matchTokenAt_19(token, context);
      case 20:
        newState = _matchTokenAt_20(token, context);
      case 21:
        newState = _matchTokenAt_21(token, context);
      case 22:
        newState = _matchTokenAt_22(token, context);
      case 23:
        newState = _matchTokenAt_23(token, context);
      case 24:
        newState = _matchTokenAt_24(token, context);
      case 25:
        newState = _matchTokenAt_25(token, context);
      case 26:
        newState = _matchTokenAt_26(token, context);
      case 27:
        newState = _matchTokenAt_27(token, context);
      case 28:
        newState = _matchTokenAt_28(token, context);
      case 29:
        newState = _matchTokenAt_29(token, context);
      case 30:
        newState = _matchTokenAt_30(token, context);
      case 31:
        newState = _matchTokenAt_31(token, context);
      case 32:
        newState = _matchTokenAt_32(token, context);
      case 33:
        newState = _matchTokenAt_33(token, context);
      case 34:
        newState = _matchTokenAt_34(token, context);
      case 35:
        newState = _matchTokenAt_35(token, context);
      case 36:
        newState = _matchTokenAt_36(token, context);
      case 37:
        newState = _matchTokenAt_37(token, context);
      case 38:
        newState = _matchTokenAt_38(token, context);
      case 39:
        newState = _matchTokenAt_39(token, context);
      case 40:
        newState = _matchTokenAt_40(token, context);
      case 41:
        newState = _matchTokenAt_41(token, context);
      case 43:
        newState = _matchTokenAt_43(token, context);
      case 44:
        newState = _matchTokenAt_44(token, context);
      case 45:
        newState = _matchTokenAt_45(token, context);
      case 46:
        newState = _matchTokenAt_46(token, context);
      case 47:
        newState = _matchTokenAt_47(token, context);
      case 48:
        newState = _matchTokenAt_48(token, context);
      case 49:
        newState = _matchTokenAt_49(token, context);
      case 50:
        newState = _matchTokenAt_50(token, context);
      default:
        throw StateError('Unknown state: $state');
    }
    return newState;
  }

  // Start
  int _matchTokenAt_0(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _build(context, token);
      return 42;
    }
    if (_matchLanguage(context, token)) {
      _startRule(context, RuleType.feature);
      _startRule(context, RuleType.featureHeader);
      _build(context, token);
      return 1;
    }
    if (_matchTagLine(context, token)) {
      _startRule(context, RuleType.feature);
      _startRule(context, RuleType.featureHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 2;
    }
    if (_matchFeatureLine(context, token)) {
      _startRule(context, RuleType.feature);
      _startRule(context, RuleType.featureHeader);
      _build(context, token);
      return 3;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 0;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 0;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Language',
      '#TagLine',
      '#FeatureLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 0;
  }

  // GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0
  int _matchTokenAt_1(Token token, ParserContext context) {
    if (_matchTagLine(context, token)) {
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 2;
    }
    if (_matchFeatureLine(context, token)) {
      _build(context, token);
      return 3;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 1;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 1;
    }

    token.detach();
    final expectedTokens = ['#TagLine', '#FeatureLine', '#Comment', '#Empty'];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 1;
  }

  // GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0
  int _matchTokenAt_2(Token token, ParserContext context) {
    if (_matchTagLine(context, token)) {
      _build(context, token);
      return 2;
    }
    if (_matchFeatureLine(context, token)) {
      _endRule(context, RuleType.tags);
      _build(context, token);
      return 3;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 2;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 2;
    }

    token.detach();
    final expectedTokens = ['#TagLine', '#FeatureLine', '#Comment', '#Empty'];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 2;
  }

  // GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0
  int _matchTokenAt_3(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.featureHeader);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 3;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 5;
    }
    if (_matchBackgroundLine(context, token)) {
      _endRule(context, RuleType.featureHeader);
      _startRule(context, RuleType.background);
      _build(context, token);
      return 6;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.featureHeader);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.featureHeader);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.featureHeader);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.featureHeader);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startRule(context, RuleType.description);
      _build(context, token);
      return 4;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Empty',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 3;
  }

  // GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>
  // Description:0>#Other:0
  int _matchTokenAt_4(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.featureHeader);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 5;
    }
    if (_matchBackgroundLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.featureHeader);
      _startRule(context, RuleType.background);
      _build(context, token);
      return 6;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.description);
        _endRule(context, RuleType.featureHeader);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.featureHeader);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.featureHeader);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.featureHeader);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _build(context, token);
      return 4;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 4;
  }

  // GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:2>#Comment:0
  int _matchTokenAt_5(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.featureHeader);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 5;
    }
    if (_matchBackgroundLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.featureHeader);
      _startRule(context, RuleType.background);
      _build(context, token);
      return 6;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endDescriptionIfNeeded(context);
        _endRule(context, RuleType.featureHeader);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.featureHeader);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.featureHeader);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.featureHeader);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startDescriptionIfNeeded(context);
      _build(context, token);
      return 4;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 5;
  }

  // GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0
  int _matchTokenAt_6(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 6;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 8;
    }
    if (_matchStepLine(context, token)) {
      _startRule(context, RuleType.step);
      _build(context, token);
      return 9;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.background);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startRule(context, RuleType.description);
      _build(context, token);
      return 7;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Empty',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 6;
  }

  // GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>
  // #Other:0
  int _matchTokenAt_7(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 8;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.description);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 9;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.description);
        _endRule(context, RuleType.background);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _build(context, token);
      return 7;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 7;
  }

  // GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:2>#Comment:0
  int _matchTokenAt_8(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 8;
    }
    if (_matchStepLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 9;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endDescriptionIfNeeded(context);
        _endRule(context, RuleType.background);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startDescriptionIfNeeded(context);
      _build(context, token);
      return 7;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 8;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0
  int _matchTokenAt_9(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchTableRow(context, token)) {
      _startRule(context, RuleType.dataTable);
      _build(context, token);
      return 10;
    }
    if (_matchDocStringSeparator(context, token)) {
      _startRule(context, RuleType.docString);
      _build(context, token);
      return 49;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 9;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.step);
        _endRule(context, RuleType.background);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 9;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 9;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#TableRow',
      '#DocStringSeparator',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 9;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>
  // DataTable:0>#TableRow:0
  int _matchTokenAt_10(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchTableRow(context, token)) {
      _build(context, token);
      return 10;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 9;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.dataTable);
        _endRule(context, RuleType.step);
        _endRule(context, RuleType.background);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 10;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 10;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#TableRow',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 10;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0
  int _matchTokenAt_11(Token token, ParserContext context) {
    if (_matchTagLine(context, token)) {
      _build(context, token);
      return 11;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.tags);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 11;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 11;
    }

    token.detach();
    final expectedTokens = ['#TagLine', '#ScenarioLine', '#Comment', '#Empty'];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 11;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
  int _matchTokenAt_12(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 12;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 14;
    }
    if (_matchStepLine(context, token)) {
      _startRule(context, RuleType.step);
      _build(context, token);
      return 15;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 17;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 18;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startRule(context, RuleType.description);
      _build(context, token);
      return 13;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Empty',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 12;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>
  // DescriptionHelper:1>Description:0>#Other:0
  int _matchTokenAt_13(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 14;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.description);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 15;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endRule(context, RuleType.description);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 17;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.description);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.description);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 18;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _build(context, token);
      return 13;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 13;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>
  // DescriptionHelper:2>#Comment:0
  int _matchTokenAt_14(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 14;
    }
    if (_matchStepLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 15;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endDescriptionIfNeeded(context);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 17;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endDescriptionIfNeeded(context);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 18;
    }
    if (_matchScenarioLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startDescriptionIfNeeded(context);
      _build(context, token);
      return 13;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 14;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>
  // #StepLine:0
  int _matchTokenAt_15(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchTableRow(context, token)) {
      _startRule(context, RuleType.dataTable);
      _build(context, token);
      return 16;
    }
    if (_matchDocStringSeparator(context, token)) {
      _startRule(context, RuleType.docString);
      _build(context, token);
      return 47;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 15;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endRule(context, RuleType.step);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 17;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.step);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 18;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 15;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 15;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#TableRow',
      '#DocStringSeparator',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 15;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>
  // StepArg:0>__alt0:0>DataTable:0>#TableRow:0
  int _matchTokenAt_16(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchTableRow(context, token)) {
      _build(context, token);
      return 16;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 15;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endRule(context, RuleType.dataTable);
        _endRule(context, RuleType.step);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 17;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.dataTable);
        _endRule(context, RuleType.step);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 18;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 16;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 16;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#TableRow',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 16;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>
  // ExamplesDefinition:0>Tags:0>#TagLine:0
  int _matchTokenAt_17(Token token, ParserContext context) {
    if (_matchTagLine(context, token)) {
      _build(context, token);
      return 17;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.tags);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 18;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 17;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 17;
    }

    token.detach();
    final expectedTokens = ['#TagLine', '#ExamplesLine', '#Comment', '#Empty'];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 17;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>
  // ExamplesDefinition:1>Examples:0>#ExamplesLine:0
  int _matchTokenAt_18(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 18;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 20;
    }
    if (_matchTableRow(context, token)) {
      _startRule(context, RuleType.examplesTable);
      _build(context, token);
      return 21;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 17;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 18;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startRule(context, RuleType.description);
      _build(context, token);
      return 19;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Empty',
      '#Comment',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 18;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>
  // ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0
  int _matchTokenAt_19(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 20;
    }
    if (_matchTableRow(context, token)) {
      _endRule(context, RuleType.description);
      _startRule(context, RuleType.examplesTable);
      _build(context, token);
      return 21;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endRule(context, RuleType.description);
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 17;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.description);
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 18;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _build(context, token);
      return 19;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 19;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>
  // ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0
  int _matchTokenAt_20(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 20;
    }
    if (_matchTableRow(context, token)) {
      _endDescriptionIfNeeded(context);
      _startRule(context, RuleType.examplesTable);
      _build(context, token);
      return 21;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endDescriptionIfNeeded(context);
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 17;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endDescriptionIfNeeded(context);
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 18;
    }
    if (_matchScenarioLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startDescriptionIfNeeded(context);
      _build(context, token);
      return 19;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 20;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>
  // ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
  int _matchTokenAt_21(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.examplesTable);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchTableRow(context, token)) {
      _build(context, token);
      return 21;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endRule(context, RuleType.examplesTable);
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 17;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.examplesTable);
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.examplesTable);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.examplesTable);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 18;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.examplesTable);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.examplesTable);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 21;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 21;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 21;
  }

  // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0
  int _matchTokenAt_22(Token token, ParserContext context) {
    if (_matchTagLine(context, token)) {
      _build(context, token);
      return 22;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.tags);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 22;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 22;
    }

    token.detach();
    final expectedTokens = ['#TagLine', '#RuleLine', '#Comment', '#Empty'];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);
    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 22;
  }

  // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>#RuleLine:0
  int _matchTokenAt_23(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.ruleHeader);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 25;
    }
    if (_matchBackgroundLine(context, token)) {
      _endRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.background);
      _build(context, token);
      return 26;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.ruleHeader);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.ruleHeader);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.ruleHeader);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startRule(context, RuleType.description);
      _build(context, token);
      return 24;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Empty',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 23;
  }

  // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>DescriptionHelper:1>
  // Description:0>#Other:0
  int _matchTokenAt_24(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.ruleHeader);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 25;
    }
    if (_matchBackgroundLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.background);
      _build(context, token);
      return 26;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.description);
        _endRule(context, RuleType.ruleHeader);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.ruleHeader);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.ruleHeader);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _build(context, token);
      return 24;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 24;
  }

  // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>DescriptionHelper:2>
  // #Comment:0
  int _matchTokenAt_25(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.ruleHeader);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 25;
    }
    if (_matchBackgroundLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.background);
      _build(context, token);
      return 26;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endDescriptionIfNeeded(context);
        _endRule(context, RuleType.ruleHeader);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.ruleHeader);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.ruleHeader);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startDescriptionIfNeeded(context);
      _build(context, token);
      return 24;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 25;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0
  int _matchTokenAt_26(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 26;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 28;
    }
    if (_matchStepLine(context, token)) {
      _startRule(context, RuleType.step);
      _build(context, token);
      return 29;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.background);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startRule(context, RuleType.description);
      _build(context, token);
      return 27;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Empty',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 26;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>
  // Description:0>#Other:0
  int _matchTokenAt_27(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 28;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.description);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 29;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.description);
        _endRule(context, RuleType.background);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _build(context, token);
      return 27;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 27;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:2>
  // #Comment:0
  int _matchTokenAt_28(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 28;
    }
    if (_matchStepLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 29;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endDescriptionIfNeeded(context);
        _endRule(context, RuleType.background);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startDescriptionIfNeeded(context);
      _build(context, token);
      return 27;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 28;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0
  int _matchTokenAt_29(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchTableRow(context, token)) {
      _startRule(context, RuleType.dataTable);
      _build(context, token);
      return 30;
    }
    if (_matchDocStringSeparator(context, token)) {
      _startRule(context, RuleType.docString);
      _build(context, token);
      return 45;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 29;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.step);
        _endRule(context, RuleType.background);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 29;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 29;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#TableRow',
      '#DocStringSeparator',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 29;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>
  // DataTable:0>#TableRow:0
  int _matchTokenAt_30(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchTableRow(context, token)) {
      _build(context, token);
      return 30;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 29;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.dataTable);
        _endRule(context, RuleType.step);
        _endRule(context, RuleType.background);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 30;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 30;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#TableRow',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 30;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0
  int _matchTokenAt_31(Token token, ParserContext context) {
    if (_matchTagLine(context, token)) {
      _build(context, token);
      return 31;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.tags);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 31;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 31;
    }

    token.detach();
    final expectedTokens = ['#TagLine', '#ScenarioLine', '#Comment', '#Empty'];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 31;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>
  // #ScenarioLine:0
  int _matchTokenAt_32(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 32;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 34;
    }
    if (_matchStepLine(context, token)) {
      _startRule(context, RuleType.step);
      _build(context, token);
      return 35;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 37;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 38;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startRule(context, RuleType.description);
      _build(context, token);
      return 33;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Empty',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 32;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>
  // DescriptionHelper:1>Description:0>#Other:0
  int _matchTokenAt_33(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 34;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.description);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 35;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endRule(context, RuleType.description);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 37;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.description);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.description);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 38;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _build(context, token);
      return 33;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 33;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>
  // DescriptionHelper:2>#Comment:0
  int _matchTokenAt_34(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 34;
    }
    if (_matchStepLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 35;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endDescriptionIfNeeded(context);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 37;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endDescriptionIfNeeded(context);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 38;
    }
    if (_matchScenarioLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startDescriptionIfNeeded(context);
      _build(context, token);
      return 33;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 34;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>
  // #StepLine:0
  int _matchTokenAt_35(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchTableRow(context, token)) {
      _startRule(context, RuleType.dataTable);
      _build(context, token);
      return 36;
    }
    if (_matchDocStringSeparator(context, token)) {
      _startRule(context, RuleType.docString);
      _build(context, token);
      return 43;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 35;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endRule(context, RuleType.step);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 37;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.step);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 38;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 35;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 35;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#TableRow',
      '#DocStringSeparator',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 35;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>
  // StepArg:0>__alt0:0>DataTable:0>#TableRow:0
  int _matchTokenAt_36(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchTableRow(context, token)) {
      _build(context, token);
      return 36;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 35;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endRule(context, RuleType.dataTable);
        _endRule(context, RuleType.step);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 37;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.dataTable);
        _endRule(context, RuleType.step);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 38;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.dataTable);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 36;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 36;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#TableRow',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 36;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>
  // ExamplesDefinition:0>Tags:0>#TagLine:0
  int _matchTokenAt_37(Token token, ParserContext context) {
    if (_matchTagLine(context, token)) {
      _build(context, token);
      return 37;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.tags);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 38;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 37;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 37;
    }

    token.detach();
    final expectedTokens = ['#TagLine', '#ExamplesLine', '#Comment', '#Empty'];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 37;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>
  // ExamplesDefinition:1>Examples:0>#ExamplesLine:0
  int _matchTokenAt_38(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 38;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 40;
    }
    if (_matchTableRow(context, token)) {
      _startRule(context, RuleType.examplesTable);
      _build(context, token);
      return 41;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 37;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 38;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startRule(context, RuleType.description);
      _build(context, token);
      return 39;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Empty',
      '#Comment',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 38;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>
  // ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0
  int _matchTokenAt_39(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 40;
    }
    if (_matchTableRow(context, token)) {
      _endRule(context, RuleType.description);
      _startRule(context, RuleType.examplesTable);
      _build(context, token);
      return 41;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endRule(context, RuleType.description);
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 37;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.description);
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 38;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.description);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _build(context, token);
      return 39;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 39;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>
  // ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0
  int _matchTokenAt_40(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 40;
    }
    if (_matchTableRow(context, token)) {
      _endDescriptionIfNeeded(context);
      _startRule(context, RuleType.examplesTable);
      _build(context, token);
      return 41;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endDescriptionIfNeeded(context);
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 37;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endDescriptionIfNeeded(context);
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 38;
    }
    if (_matchScenarioLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endDescriptionIfNeeded(context);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchOther(context, token)) {
      _startDescriptionIfNeeded(context);
      _build(context, token);
      return 39;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#Comment',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 40;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>
  // ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
  int _matchTokenAt_41(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.examplesTable);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchTableRow(context, token)) {
      _build(context, token);
      return 41;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endRule(context, RuleType.examplesTable);
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 37;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.examplesTable);
        _endRule(context, RuleType.examples);
        _endRule(context, RuleType.examplesDefinition);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.examplesTable);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.examplesTable);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 38;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.examplesTable);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.examplesTable);
      _endRule(context, RuleType.examples);
      _endRule(context, RuleType.examplesDefinition);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 41;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 41;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 41;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>
  // StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
  int _matchTokenAt_43(Token token, ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
      _build(context, token);
      return 44;
    }
    if (_matchOther(context, token)) {
      _build(context, token);
      return 43;
    }

    token.detach();
    final expectedTokens = ['#DocStringSeparator', '#Other'];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 43;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>
  // StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
  int _matchTokenAt_44(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 35;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endRule(context, RuleType.docString);
        _endRule(context, RuleType.step);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 37;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.docString);
        _endRule(context, RuleType.step);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 38;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 44;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 44;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 44;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>
  // DocString:0>#DocStringSeparator:0
  int _matchTokenAt_45(Token token, ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
      _build(context, token);
      return 46;
    }
    if (_matchOther(context, token)) {
      _build(context, token);
      return 45;
    }

    token.detach();
    final expectedTokens = ['#DocStringSeparator', '#Other'];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 45;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>
  // DocString:2>#DocStringSeparator:0
  int _matchTokenAt_46(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 29;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.docString);
        _endRule(context, RuleType.step);
        _endRule(context, RuleType.background);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 31;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 32;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.rule);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 46;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 46;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 46;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>
  // StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
  int _matchTokenAt_47(Token token, ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
      _build(context, token);
      return 48;
    }
    if (_matchOther(context, token)) {
      _build(context, token);
      return 47;
    }

    token.detach();
    final expectedTokens = ['#DocStringSeparator', '#Other'];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 47;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>
  // StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
  int _matchTokenAt_48(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 15;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_1(context, token)) {
        _endRule(context, RuleType.docString);
        _endRule(context, RuleType.step);
        _startRule(context, RuleType.examplesDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 17;
      }
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.docString);
        _endRule(context, RuleType.step);
        _endRule(context, RuleType.scenario);
        _endRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchExamplesLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.examplesDefinition);
      _startRule(context, RuleType.examples);
      _build(context, token);
      return 18;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.scenario);
      _endRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 48;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 48;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 48;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>
  // DocString:0>#DocStringSeparator:0
  int _matchTokenAt_49(Token token, ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
      _build(context, token);
      return 50;
    }
    if (_matchOther(context, token)) {
      _build(context, token);
      return 49;
    }

    token.detach();
    final expectedTokens = ['#DocStringSeparator', '#Other'];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 49;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>
  // DocString:2>#DocStringSeparator:0
  int _matchTokenAt_50(Token token, ParserContext context) {
    if (_matchEof(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _endRule(context, RuleType.feature);
      _build(context, token);
      return 42;
    }
    if (_matchStepLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _startRule(context, RuleType.step);
      _build(context, token);
      return 9;
    }
    if (_matchTagLine(context, token)) {
      if (_lookahead_0(context, token)) {
        _endRule(context, RuleType.docString);
        _endRule(context, RuleType.step);
        _endRule(context, RuleType.background);
        _startRule(context, RuleType.scenarioDefinition);
        _startRule(context, RuleType.tags);
        _build(context, token);
        return 11;
      }
    }
    if (_matchTagLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _startRule(context, RuleType.tags);
      _build(context, token);
      return 22;
    }
    if (_matchScenarioLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.scenarioDefinition);
      _startRule(context, RuleType.scenario);
      _build(context, token);
      return 12;
    }
    if (_matchRuleLine(context, token)) {
      _endRule(context, RuleType.docString);
      _endRule(context, RuleType.step);
      _endRule(context, RuleType.background);
      _startRule(context, RuleType.rule);
      _startRule(context, RuleType.ruleHeader);
      _build(context, token);
      return 23;
    }
    if (_matchComment(context, token)) {
      _build(context, token);
      return 50;
    }
    if (_matchEmpty(context, token)) {
      _build(context, token);
      return 50;
    }

    token.detach();
    final expectedTokens = [
      '#EOF',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens)
            : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 50;
  }

  bool _lookahead_0(ParserContext context, Token currentToken) {
    currentToken.detach();
    Token token;
    final queue = Queue<Token>();
    var match = false;
    do {
      token = _readToken(context)..detach();
      queue.add(token);

      if (false || _matchScenarioLine(context, token)) {
        match = true;
        break;
      }
    } while (false ||
        _matchEmpty(context, token) ||
        _matchComment(context, token) ||
        _matchTagLine(context, token));

    context.tokenQueue.addAll(queue);

    return match;
  }

  bool _lookahead_1(ParserContext context, Token currentToken) {
    currentToken.detach();
    Token token;
    final queue = Queue<Token>();
    var match = false;
    do {
      token = _readToken(context)..detach();
      queue.add(token);

      if (false || _matchExamplesLine(context, token)) {
        match = true;
        break;
      }
    } while (false ||
        _matchEmpty(context, token) ||
        _matchComment(context, token) ||
        _matchTagLine(context, token));

    context.tokenQueue.addAll(queue);

    return match;
  }
}
