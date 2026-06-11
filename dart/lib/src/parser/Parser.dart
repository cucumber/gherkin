import 'dart:collection';
import 'package:gherkin/exceptions.dart';
import 'package:gherkin/language.dart';

import 'i_builder.dart';
import 'i_token_matcher.dart';
import 'i_token_scanner.dart';
import 'parser_context.dart';
import 'rule_type.dart';

class Parser<T> {
  final IBuilder<T> _builder;
  bool _descriptionOpen = false;

  bool stopAtFirstError = false;

  Parser(this._builder);

  T parse(ITokenScanner tokenScanner, ITokenMatcher tokenMatcher) {
    _descriptionOpen = false;
    _builder.reset();
    tokenMatcher.reset();

    var context = ParserContext(
      tokenScanner,
      tokenMatcher,
      Queue<Token>(),
      <ParserException>[],
    );

    startRule(context, RuleType.gherkinDocument);
    var state = 0;
    Token token;
    do {
      token = _readToken(context);
      state = _matchToken(state, token, context);
    } while (!token.isEof);

    endRule(context, RuleType.gherkinDocument);

    if (context.errors.isNotEmpty) {
      throw CompositeParserException(context.errors);
    }

    return _builder.result;
  }

  void addError(ParserContext context, ParserException error) {
    // Deduplicate by (message, line, column) so the same parse-error at the
    // same location is not reported twice, but distinct errors with an
    // identical message at different locations are kept.
    for (var e in context.errors) {
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
      for (var error in compositeParserException.errors) {
        addError(context, error);
      }
    } on ParserException catch (error) {
      addError(context, error);
    }
    return defaultValue;
  }

  void build(ParserContext context, Token token) =>
      _handleAstError(context, () => _builder.build(token));

  void startRule(ParserContext context, RuleType ruleType) =>
      _handleAstError(context, () {
        _builder.startRule(ruleType);
        if (ruleType == RuleType.description) {
          _descriptionOpen = true;
        }
      });

  void endRule(ParserContext context, RuleType ruleType) =>
      _handleAstError(context, () {
        _builder.endRule(ruleType);
        if (ruleType == RuleType.description) {
          _descriptionOpen = false;
        }
      });

  void startDescriptionIfNeeded(ParserContext context) {
    if (!_descriptionOpen) {
      startRule(context, RuleType.description);
    }
  }

  void endDescriptionIfNeeded(ParserContext context) {
    if (_descriptionOpen) {
      endRule(context, RuleType.description);
    }
  }

  Token _readToken(ParserContext context) =>
      context.tokenQueue.isNotEmpty
          ? context.tokenQueue.removeFirst()
          : context.tokenScanner.read();

  bool matchEof(ParserContext context, Token token) {
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchEof(token),
      false,
    );
  }

  bool matchEmpty(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchEmpty(token),
      false,
    );
  }

  bool matchComment(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchComment(token),
      false,
    );
  }

  bool matchTagLine(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchTagLine(token),
      false,
    );
  }

  bool matchFeatureLine(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchFeatureLine(token),
      false,
    );
  }

  bool matchRuleLine(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchRuleLine(token),
      false,
    );
  }

  bool matchBackgroundLine(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchBackgroundLine(token),
      false,
    );
  }

  bool matchScenarioLine(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchScenarioLine(token),
      false,
    );
  }

  bool matchExamplesLine(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchExamplesLine(token),
      false,
    );
  }

  bool matchStepLine(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchStepLine(token),
      false,
    );
  }

  bool matchDocStringSeparator(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchDocStringSeparator(token),
      false,
    );
  }

  bool matchTableRow(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchTableRow(token),
      false,
    );
  }

  bool matchLanguage(ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchLanguage(token),
      false,
    );
  }

  bool matchOther(ParserContext context, Token token) {
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
        newState = matchTokenAt_0(token, context);
        break;
      case 1:
        newState = matchTokenAt_1(token, context);
        break;
      case 2:
        newState = matchTokenAt_2(token, context);
        break;
      case 3:
        newState = matchTokenAt_3(token, context);
        break;
      case 4:
        newState = matchTokenAt_4(token, context);
        break;
      case 5:
        newState = matchTokenAt_5(token, context);
        break;
      case 6:
        newState = matchTokenAt_6(token, context);
        break;
      case 7:
        newState = matchTokenAt_7(token, context);
        break;
      case 8:
        newState = matchTokenAt_8(token, context);
        break;
      case 9:
        newState = matchTokenAt_9(token, context);
        break;
      case 10:
        newState = matchTokenAt_10(token, context);
        break;
      case 11:
        newState = matchTokenAt_11(token, context);
        break;
      case 12:
        newState = matchTokenAt_12(token, context);
        break;
      case 13:
        newState = matchTokenAt_13(token, context);
        break;
      case 14:
        newState = matchTokenAt_14(token, context);
        break;
      case 15:
        newState = matchTokenAt_15(token, context);
        break;
      case 16:
        newState = matchTokenAt_16(token, context);
        break;
      case 17:
        newState = matchTokenAt_17(token, context);
        break;
      case 18:
        newState = matchTokenAt_18(token, context);
        break;
      case 19:
        newState = matchTokenAt_19(token, context);
        break;
      case 20:
        newState = matchTokenAt_20(token, context);
        break;
      case 21:
        newState = matchTokenAt_21(token, context);
        break;
      case 22:
        newState = matchTokenAt_22(token, context);
        break;
      case 23:
        newState = matchTokenAt_23(token, context);
        break;
      case 24:
        newState = matchTokenAt_24(token, context);
        break;
      case 25:
        newState = matchTokenAt_25(token, context);
        break;
      case 26:
        newState = matchTokenAt_26(token, context);
        break;
      case 27:
        newState = matchTokenAt_27(token, context);
        break;
      case 28:
        newState = matchTokenAt_28(token, context);
        break;
      case 29:
        newState = matchTokenAt_29(token, context);
        break;
      case 30:
        newState = matchTokenAt_30(token, context);
        break;
      case 31:
        newState = matchTokenAt_31(token, context);
        break;
      case 32:
        newState = matchTokenAt_32(token, context);
        break;
      case 33:
        newState = matchTokenAt_33(token, context);
        break;
      case 34:
        newState = matchTokenAt_34(token, context);
        break;
      case 35:
        newState = matchTokenAt_35(token, context);
        break;
      case 36:
        newState = matchTokenAt_36(token, context);
        break;
      case 37:
        newState = matchTokenAt_37(token, context);
        break;
      case 38:
        newState = matchTokenAt_38(token, context);
        break;
      case 39:
        newState = matchTokenAt_39(token, context);
        break;
      case 40:
        newState = matchTokenAt_40(token, context);
        break;
      case 41:
        newState = matchTokenAt_41(token, context);
        break;
      case 43:
        newState = matchTokenAt_43(token, context);
        break;
      case 44:
        newState = matchTokenAt_44(token, context);
        break;
      case 45:
        newState = matchTokenAt_45(token, context);
        break;
      case 46:
        newState = matchTokenAt_46(token, context);
        break;
      case 47:
        newState = matchTokenAt_47(token, context);
        break;
      case 48:
        newState = matchTokenAt_48(token, context);
        break;
      case 49:
        newState = matchTokenAt_49(token, context);
        break;
      case 50:
        newState = matchTokenAt_50(token, context);
        break;
      default:
        throw StateError('Unknown state: $state');
    }
    return newState;
  }

  // Start
  int matchTokenAt_0(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      build(context, token);
      return 42;
    }
    if (matchLanguage(context, token)) {
      startRule(context, RuleType.feature);
      startRule(context, RuleType.featureHeader);
      build(context, token);
      return 1;
    }
    if (matchTagLine(context, token)) {
      startRule(context, RuleType.feature);
      startRule(context, RuleType.featureHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 2;
    }
    if (matchFeatureLine(context, token)) {
      startRule(context, RuleType.feature);
      startRule(context, RuleType.featureHeader);
      build(context, token);
      return 3;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 0;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 0;
    }

    final stateComment = 'State: 0 - Start';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Language',
      '#TagLine',
      '#FeatureLine',
      '#Comment',
      '#Empty',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 0;
  }

  // GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0
  int matchTokenAt_1(Token token, ParserContext context) {
    if (matchTagLine(context, token)) {
      startRule(context, RuleType.tags);
      build(context, token);
      return 2;
    }
    if (matchFeatureLine(context, token)) {
      build(context, token);
      return 3;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 1;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 1;
    }

    final stateComment =
        'State: 1 - GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0';
    token.detach();
    var expectedTokens = ['#TagLine', '#FeatureLine', '#Comment', '#Empty'];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 1;
  }

  // GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0
  int matchTokenAt_2(Token token, ParserContext context) {
    if (matchTagLine(context, token)) {
      build(context, token);
      return 2;
    }
    if (matchFeatureLine(context, token)) {
      endRule(context, RuleType.tags);
      build(context, token);
      return 3;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 2;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 2;
    }

    final stateComment =
        'State: 2 - GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0';
    token.detach();
    var expectedTokens = ['#TagLine', '#FeatureLine', '#Comment', '#Empty'];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 2;
  }

  // GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0
  int matchTokenAt_3(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.featureHeader);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 3;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 5;
    }
    if (matchBackgroundLine(context, token)) {
      endRule(context, RuleType.featureHeader);
      startRule(context, RuleType.background);
      build(context, token);
      return 6;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.featureHeader);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.featureHeader);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.featureHeader);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.featureHeader);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startRule(context, RuleType.description);
      build(context, token);
      return 4;
    }

    final stateComment =
        'State: 3 - GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Empty',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 3;
  }

  // GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>#Other:0
  int matchTokenAt_4(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.featureHeader);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 5;
    }
    if (matchBackgroundLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.featureHeader);
      startRule(context, RuleType.background);
      build(context, token);
      return 6;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.description);
        endRule(context, RuleType.featureHeader);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.featureHeader);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.featureHeader);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.featureHeader);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      build(context, token);
      return 4;
    }

    final stateComment =
        'State: 4 - GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>#Other:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 4;
  }

  // GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:2>#Comment:0
  int matchTokenAt_5(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.featureHeader);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 5;
    }
    if (matchBackgroundLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.featureHeader);
      startRule(context, RuleType.background);
      build(context, token);
      return 6;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endDescriptionIfNeeded(context);
        endRule(context, RuleType.featureHeader);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.featureHeader);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.featureHeader);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.featureHeader);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startDescriptionIfNeeded(context);
      build(context, token);
      return 4;
    }

    final stateComment =
        'State: 5 - GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:2>#Comment:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 5;
  }

  // GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0
  int matchTokenAt_6(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.background);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 6;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 8;
    }
    if (matchStepLine(context, token)) {
      startRule(context, RuleType.step);
      build(context, token);
      return 9;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.background);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.background);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.background);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.background);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startRule(context, RuleType.description);
      build(context, token);
      return 7;
    }

    final stateComment =
        'State: 6 - GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Empty',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 6;
  }

  // GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>#Other:0
  int matchTokenAt_7(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.background);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 8;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.description);
      startRule(context, RuleType.step);
      build(context, token);
      return 9;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.description);
        endRule(context, RuleType.background);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.background);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.background);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.background);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      build(context, token);
      return 7;
    }

    final stateComment =
        'State: 7 - GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>#Other:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 7;
  }

  // GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:2>#Comment:0
  int matchTokenAt_8(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.background);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 8;
    }
    if (matchStepLine(context, token)) {
      endDescriptionIfNeeded(context);
      startRule(context, RuleType.step);
      build(context, token);
      return 9;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endDescriptionIfNeeded(context);
        endRule(context, RuleType.background);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.background);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.background);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.background);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startDescriptionIfNeeded(context);
      build(context, token);
      return 7;
    }

    final stateComment =
        'State: 8 - GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:2>#Comment:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 8;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0
  int matchTokenAt_9(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchTableRow(context, token)) {
      startRule(context, RuleType.dataTable);
      build(context, token);
      return 10;
    }
    if (matchDocStringSeparator(context, token)) {
      startRule(context, RuleType.docString);
      build(context, token);
      return 49;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.step);
      startRule(context, RuleType.step);
      build(context, token);
      return 9;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.step);
        endRule(context, RuleType.background);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 9;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 9;
    }

    final stateComment =
        'State: 9 - GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0';
    token.detach();
    var expectedTokens = [
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
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 9;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
  int matchTokenAt_10(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchTableRow(context, token)) {
      build(context, token);
      return 10;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      startRule(context, RuleType.step);
      build(context, token);
      return 9;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.dataTable);
        endRule(context, RuleType.step);
        endRule(context, RuleType.background);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 10;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 10;
    }

    final stateComment =
        'State: 10 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#TableRow',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 10;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0
  int matchTokenAt_11(Token token, ParserContext context) {
    if (matchTagLine(context, token)) {
      build(context, token);
      return 11;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.tags);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 11;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 11;
    }

    final stateComment =
        'State: 11 - GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0';
    token.detach();
    var expectedTokens = ['#TagLine', '#ScenarioLine', '#Comment', '#Empty'];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 11;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
  int matchTokenAt_12(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 12;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 14;
    }
    if (matchStepLine(context, token)) {
      startRule(context, RuleType.step);
      build(context, token);
      return 15;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 17;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 18;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startRule(context, RuleType.description);
      build(context, token);
      return 13;
    }

    final stateComment =
        'State: 12 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0';
    token.detach();
    var expectedTokens = [
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
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 12;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0
  int matchTokenAt_13(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 14;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.description);
      startRule(context, RuleType.step);
      build(context, token);
      return 15;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endRule(context, RuleType.description);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 17;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.description);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.description);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 18;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      build(context, token);
      return 13;
    }

    final stateComment =
        'State: 13 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 13;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0
  int matchTokenAt_14(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 14;
    }
    if (matchStepLine(context, token)) {
      endDescriptionIfNeeded(context);
      startRule(context, RuleType.step);
      build(context, token);
      return 15;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endDescriptionIfNeeded(context);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 17;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endDescriptionIfNeeded(context);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endDescriptionIfNeeded(context);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 18;
    }
    if (matchScenarioLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startDescriptionIfNeeded(context);
      build(context, token);
      return 13;
    }

    final stateComment =
        'State: 14 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 14;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
  int matchTokenAt_15(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchTableRow(context, token)) {
      startRule(context, RuleType.dataTable);
      build(context, token);
      return 16;
    }
    if (matchDocStringSeparator(context, token)) {
      startRule(context, RuleType.docString);
      build(context, token);
      return 47;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.step);
      startRule(context, RuleType.step);
      build(context, token);
      return 15;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endRule(context, RuleType.step);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 17;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.step);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.step);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 18;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 15;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 15;
    }

    final stateComment =
        'State: 15 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0';
    token.detach();
    var expectedTokens = [
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
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 15;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
  int matchTokenAt_16(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchTableRow(context, token)) {
      build(context, token);
      return 16;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      startRule(context, RuleType.step);
      build(context, token);
      return 15;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endRule(context, RuleType.dataTable);
        endRule(context, RuleType.step);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 17;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.dataTable);
        endRule(context, RuleType.step);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 18;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 16;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 16;
    }

    final stateComment =
        'State: 16 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0';
    token.detach();
    var expectedTokens = [
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
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 16;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
  int matchTokenAt_17(Token token, ParserContext context) {
    if (matchTagLine(context, token)) {
      build(context, token);
      return 17;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.tags);
      startRule(context, RuleType.examples);
      build(context, token);
      return 18;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 17;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 17;
    }

    final stateComment =
        'State: 17 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0';
    token.detach();
    var expectedTokens = ['#TagLine', '#ExamplesLine', '#Comment', '#Empty'];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 17;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
  int matchTokenAt_18(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 18;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 20;
    }
    if (matchTableRow(context, token)) {
      startRule(context, RuleType.examplesTable);
      build(context, token);
      return 21;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 17;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 18;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startRule(context, RuleType.description);
      build(context, token);
      return 19;
    }

    final stateComment =
        'State: 18 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0';
    token.detach();
    var expectedTokens = [
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
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 18;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0
  int matchTokenAt_19(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 20;
    }
    if (matchTableRow(context, token)) {
      endRule(context, RuleType.description);
      startRule(context, RuleType.examplesTable);
      build(context, token);
      return 21;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endRule(context, RuleType.description);
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 17;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.description);
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 18;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      build(context, token);
      return 19;
    }

    final stateComment =
        'State: 19 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 19;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0
  int matchTokenAt_20(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 20;
    }
    if (matchTableRow(context, token)) {
      endDescriptionIfNeeded(context);
      startRule(context, RuleType.examplesTable);
      build(context, token);
      return 21;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endDescriptionIfNeeded(context);
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 17;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endDescriptionIfNeeded(context);
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 18;
    }
    if (matchScenarioLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startDescriptionIfNeeded(context);
      build(context, token);
      return 19;
    }

    final stateComment =
        'State: 20 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 20;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
  int matchTokenAt_21(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.examplesTable);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchTableRow(context, token)) {
      build(context, token);
      return 21;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endRule(context, RuleType.examplesTable);
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 17;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.examplesTable);
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.examplesTable);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.examplesTable);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 18;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.examplesTable);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.examplesTable);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 21;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 21;
    }

    final stateComment =
        'State: 21 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 21;
  }

  // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0
  int matchTokenAt_22(Token token, ParserContext context) {
    if (matchTagLine(context, token)) {
      build(context, token);
      return 22;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.tags);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 22;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 22;
    }

    final stateComment =
        'State: 22 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0';
    token.detach();
    var expectedTokens = ['#TagLine', '#RuleLine', '#Comment', '#Empty'];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);
    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 22;
  }

  // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>#RuleLine:0
  int matchTokenAt_23(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.ruleHeader);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 25;
    }
    if (matchBackgroundLine(context, token)) {
      endRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.background);
      build(context, token);
      return 26;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.ruleHeader);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.ruleHeader);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.ruleHeader);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startRule(context, RuleType.description);
      build(context, token);
      return 24;
    }

    final stateComment =
        'State: 23 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>#RuleLine:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Empty',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 23;
  }

  // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>DescriptionHelper:1>Description:0>#Other:0
  int matchTokenAt_24(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.ruleHeader);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 25;
    }
    if (matchBackgroundLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.background);
      build(context, token);
      return 26;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.description);
        endRule(context, RuleType.ruleHeader);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.ruleHeader);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.ruleHeader);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      build(context, token);
      return 24;
    }

    final stateComment =
        'State: 24 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>DescriptionHelper:1>Description:0>#Other:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 24;
  }

  // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>DescriptionHelper:2>#Comment:0
  int matchTokenAt_25(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.ruleHeader);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 25;
    }
    if (matchBackgroundLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.background);
      build(context, token);
      return 26;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endDescriptionIfNeeded(context);
        endRule(context, RuleType.ruleHeader);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.ruleHeader);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.ruleHeader);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startDescriptionIfNeeded(context);
      build(context, token);
      return 24;
    }

    final stateComment =
        'State: 25 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>DescriptionHelper:2>#Comment:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 25;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0
  int matchTokenAt_26(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 26;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 28;
    }
    if (matchStepLine(context, token)) {
      startRule(context, RuleType.step);
      build(context, token);
      return 29;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.background);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.background);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startRule(context, RuleType.description);
      build(context, token);
      return 27;
    }

    final stateComment =
        'State: 26 - GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Empty',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 26;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>#Other:0
  int matchTokenAt_27(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 28;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.description);
      startRule(context, RuleType.step);
      build(context, token);
      return 29;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.description);
        endRule(context, RuleType.background);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.background);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      build(context, token);
      return 27;
    }

    final stateComment =
        'State: 27 - GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>#Other:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 27;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:2>#Comment:0
  int matchTokenAt_28(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 28;
    }
    if (matchStepLine(context, token)) {
      endDescriptionIfNeeded(context);
      startRule(context, RuleType.step);
      build(context, token);
      return 29;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endDescriptionIfNeeded(context);
        endRule(context, RuleType.background);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.background);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startDescriptionIfNeeded(context);
      build(context, token);
      return 27;
    }

    final stateComment =
        'State: 28 - GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:2>#Comment:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 28;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0
  int matchTokenAt_29(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchTableRow(context, token)) {
      startRule(context, RuleType.dataTable);
      build(context, token);
      return 30;
    }
    if (matchDocStringSeparator(context, token)) {
      startRule(context, RuleType.docString);
      build(context, token);
      return 45;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.step);
      startRule(context, RuleType.step);
      build(context, token);
      return 29;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.step);
        endRule(context, RuleType.background);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 29;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 29;
    }

    final stateComment =
        'State: 29 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0';
    token.detach();
    var expectedTokens = [
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
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 29;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
  int matchTokenAt_30(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchTableRow(context, token)) {
      build(context, token);
      return 30;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      startRule(context, RuleType.step);
      build(context, token);
      return 29;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.dataTable);
        endRule(context, RuleType.step);
        endRule(context, RuleType.background);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 30;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 30;
    }

    final stateComment =
        'State: 30 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#TableRow',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 30;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0
  int matchTokenAt_31(Token token, ParserContext context) {
    if (matchTagLine(context, token)) {
      build(context, token);
      return 31;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.tags);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 31;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 31;
    }

    final stateComment =
        'State: 31 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0';
    token.detach();
    var expectedTokens = ['#TagLine', '#ScenarioLine', '#Comment', '#Empty'];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 31;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
  int matchTokenAt_32(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 32;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 34;
    }
    if (matchStepLine(context, token)) {
      startRule(context, RuleType.step);
      build(context, token);
      return 35;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 37;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 38;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startRule(context, RuleType.description);
      build(context, token);
      return 33;
    }

    final stateComment =
        'State: 32 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0';
    token.detach();
    var expectedTokens = [
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
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 32;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0
  int matchTokenAt_33(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 34;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.description);
      startRule(context, RuleType.step);
      build(context, token);
      return 35;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endRule(context, RuleType.description);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 37;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.description);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.description);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 38;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      build(context, token);
      return 33;
    }

    final stateComment =
        'State: 33 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 33;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0
  int matchTokenAt_34(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 34;
    }
    if (matchStepLine(context, token)) {
      endDescriptionIfNeeded(context);
      startRule(context, RuleType.step);
      build(context, token);
      return 35;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endDescriptionIfNeeded(context);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 37;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endDescriptionIfNeeded(context);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endDescriptionIfNeeded(context);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 38;
    }
    if (matchScenarioLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startDescriptionIfNeeded(context);
      build(context, token);
      return 33;
    }

    final stateComment =
        'State: 34 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 34;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
  int matchTokenAt_35(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchTableRow(context, token)) {
      startRule(context, RuleType.dataTable);
      build(context, token);
      return 36;
    }
    if (matchDocStringSeparator(context, token)) {
      startRule(context, RuleType.docString);
      build(context, token);
      return 43;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.step);
      startRule(context, RuleType.step);
      build(context, token);
      return 35;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endRule(context, RuleType.step);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 37;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.step);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.step);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 38;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 35;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 35;
    }

    final stateComment =
        'State: 35 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0';
    token.detach();
    var expectedTokens = [
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
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 35;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
  int matchTokenAt_36(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchTableRow(context, token)) {
      build(context, token);
      return 36;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      startRule(context, RuleType.step);
      build(context, token);
      return 35;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endRule(context, RuleType.dataTable);
        endRule(context, RuleType.step);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 37;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.dataTable);
        endRule(context, RuleType.step);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 38;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.dataTable);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 36;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 36;
    }

    final stateComment =
        'State: 36 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0';
    token.detach();
    var expectedTokens = [
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
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 36;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
  int matchTokenAt_37(Token token, ParserContext context) {
    if (matchTagLine(context, token)) {
      build(context, token);
      return 37;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.tags);
      startRule(context, RuleType.examples);
      build(context, token);
      return 38;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 37;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 37;
    }

    final stateComment =
        'State: 37 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0';
    token.detach();
    var expectedTokens = ['#TagLine', '#ExamplesLine', '#Comment', '#Empty'];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 37;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
  int matchTokenAt_38(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 38;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 40;
    }
    if (matchTableRow(context, token)) {
      startRule(context, RuleType.examplesTable);
      build(context, token);
      return 41;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 37;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 38;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startRule(context, RuleType.description);
      build(context, token);
      return 39;
    }

    final stateComment =
        'State: 38 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0';
    token.detach();
    var expectedTokens = [
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
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 38;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0
  int matchTokenAt_39(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 40;
    }
    if (matchTableRow(context, token)) {
      endRule(context, RuleType.description);
      startRule(context, RuleType.examplesTable);
      build(context, token);
      return 41;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endRule(context, RuleType.description);
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 37;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.description);
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 38;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.description);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      build(context, token);
      return 39;
    }

    final stateComment =
        'State: 39 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 39;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0
  int matchTokenAt_40(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 40;
    }
    if (matchTableRow(context, token)) {
      endDescriptionIfNeeded(context);
      startRule(context, RuleType.examplesTable);
      build(context, token);
      return 41;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endDescriptionIfNeeded(context);
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 37;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endDescriptionIfNeeded(context);
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 38;
    }
    if (matchScenarioLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endDescriptionIfNeeded(context);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchOther(context, token)) {
      startDescriptionIfNeeded(context);
      build(context, token);
      return 39;
    }

    final stateComment =
        'State: 40 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#Comment',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 40;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
  int matchTokenAt_41(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.examplesTable);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchTableRow(context, token)) {
      build(context, token);
      return 41;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endRule(context, RuleType.examplesTable);
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 37;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.examplesTable);
        endRule(context, RuleType.examples);
        endRule(context, RuleType.examplesDefinition);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.examplesTable);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.examplesTable);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 38;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.examplesTable);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.examplesTable);
      endRule(context, RuleType.examples);
      endRule(context, RuleType.examplesDefinition);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 41;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 41;
    }

    final stateComment =
        'State: 41 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 41;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
  int matchTokenAt_43(Token token, ParserContext context) {
    if (matchDocStringSeparator(context, token)) {
      build(context, token);
      return 44;
    }
    if (matchOther(context, token)) {
      build(context, token);
      return 43;
    }

    final stateComment =
        'State: 43 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0';
    token.detach();
    var expectedTokens = ['#DocStringSeparator', '#Other'];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 43;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
  int matchTokenAt_44(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      startRule(context, RuleType.step);
      build(context, token);
      return 35;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endRule(context, RuleType.docString);
        endRule(context, RuleType.step);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 37;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.docString);
        endRule(context, RuleType.step);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 38;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 44;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 44;
    }

    final stateComment =
        'State: 44 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 44;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
  int matchTokenAt_45(Token token, ParserContext context) {
    if (matchDocStringSeparator(context, token)) {
      build(context, token);
      return 46;
    }
    if (matchOther(context, token)) {
      build(context, token);
      return 45;
    }

    final stateComment =
        'State: 44 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0';
    token.detach();
    var expectedTokens = ['#DocStringSeparator', '#Other'];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 45;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
  int matchTokenAt_46(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      startRule(context, RuleType.step);
      build(context, token);
      return 29;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.docString);
        endRule(context, RuleType.step);
        endRule(context, RuleType.background);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 31;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 32;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      endRule(context, RuleType.rule);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 46;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 46;
    }

    final stateComment =
        'State: 46 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 46;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
  int matchTokenAt_47(Token token, ParserContext context) {
    if (matchDocStringSeparator(context, token)) {
      build(context, token);
      return 48;
    }
    if (matchOther(context, token)) {
      build(context, token);
      return 47;
    }

    final stateComment =
        'State: 47 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0';
    token.detach();
    var expectedTokens = ['#DocStringSeparator', '#Other'];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 47;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
  int matchTokenAt_48(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      startRule(context, RuleType.step);
      build(context, token);
      return 15;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_1(context, token)) {
        endRule(context, RuleType.docString);
        endRule(context, RuleType.step);
        startRule(context, RuleType.examplesDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 17;
      }
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.docString);
        endRule(context, RuleType.step);
        endRule(context, RuleType.scenario);
        endRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchExamplesLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      startRule(context, RuleType.examplesDefinition);
      startRule(context, RuleType.examples);
      build(context, token);
      return 18;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.scenario);
      endRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 48;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 48;
    }

    final stateComment =
        'State: 48 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 48;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
  int matchTokenAt_49(Token token, ParserContext context) {
    if (matchDocStringSeparator(context, token)) {
      build(context, token);
      return 50;
    }
    if (matchOther(context, token)) {
      build(context, token);
      return 49;
    }

    final stateComment =
        'State: 49 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0';
    token.detach();
    var expectedTokens = ['#DocStringSeparator', '#Other'];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 49;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
  int matchTokenAt_50(Token token, ParserContext context) {
    if (matchEof(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      endRule(context, RuleType.feature);
      build(context, token);
      return 42;
    }
    if (matchStepLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      startRule(context, RuleType.step);
      build(context, token);
      return 9;
    }
    if (matchTagLine(context, token)) {
      if (lookahead_0(context, token)) {
        endRule(context, RuleType.docString);
        endRule(context, RuleType.step);
        endRule(context, RuleType.background);
        startRule(context, RuleType.scenarioDefinition);
        startRule(context, RuleType.tags);
        build(context, token);
        return 11;
      }
    }
    if (matchTagLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      startRule(context, RuleType.tags);
      build(context, token);
      return 22;
    }
    if (matchScenarioLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      startRule(context, RuleType.scenarioDefinition);
      startRule(context, RuleType.scenario);
      build(context, token);
      return 12;
    }
    if (matchRuleLine(context, token)) {
      endRule(context, RuleType.docString);
      endRule(context, RuleType.step);
      endRule(context, RuleType.background);
      startRule(context, RuleType.rule);
      startRule(context, RuleType.ruleHeader);
      build(context, token);
      return 23;
    }
    if (matchComment(context, token)) {
      build(context, token);
      return 50;
    }
    if (matchEmpty(context, token)) {
      build(context, token);
      return 50;
    }

    final stateComment =
        'State: 50 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0';
    token.detach();
    var expectedTokens = [
      '#EOF',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    var error =
        token.isEof
            ? UnexpectedEofException(token, expectedTokens, stateComment)
            : UnexpectedTokenException(token, expectedTokens, stateComment);

    if (stopAtFirstError) {
      throw error;
    }

    addError(context, error);
    return 50;
  }

  bool lookahead_0(ParserContext context, Token currentToken) {
    currentToken.detach();
    Token token;
    var queue = Queue<Token>();
    var match = false;
    do {
      token = _readToken(context);
      token.detach();
      queue.add(token);

      if (false || matchScenarioLine(context, token)) {
        match = true;
        break;
      }
    } while (false ||
        matchEmpty(context, token) ||
        matchComment(context, token) ||
        matchTagLine(context, token));

    context.tokenQueue.addAll(queue);

    return match;
  }

  bool lookahead_1(ParserContext context, Token currentToken) {
    currentToken.detach();
    Token token;
    var queue = Queue<Token>();
    var match = false;
    do {
      token = _readToken(context);
      token.detach();
      queue.add(token);

      if (false || matchExamplesLine(context, token)) {
        match = true;
        break;
      }
    } while (false ||
        matchEmpty(context, token) ||
        matchComment(context, token) ||
        matchTagLine(context, token));

    context.tokenQueue.addAll(queue);

    return match;
  }
}
