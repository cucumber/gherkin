// GENERATED FILE - DO NOT MODIFY BY HAND.
//
// This file was generated from `gherkin-dart.razor` by
// [Berp](https://github.com/gasparnagy/berp) using the shared `../gherkin.berp`
// grammar.
// dart format off
import 'dart:collection';

import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/builder.dart';
import 'package:cucumber_gherkin/src/parser/token_scanner.dart';

enum TokenType {
  none,
  eOF,
  empty,
  comment,
  tagLine,
  featureLine,
  ruleLine,
  backgroundLine,
  scenarioLine,
  examplesLine,
  stepLine,
  docStringSeparator,
  tableRow,
  language,
  other,
}

enum RuleType {
  none,
  eOF,
  empty,
  comment,
  tagLine,
  featureLine,
  ruleLine,
  backgroundLine,
  scenarioLine,
  examplesLine,
  stepLine,
  docStringSeparator,
  tableRow,
  language,
  other,
  gherkinDocument,
  feature,
  featureHeader,
  rule,
  ruleHeader,
  background,
  scenarioDefinition,
  scenario,
  examplesDefinition,
  examples,
  examplesTable,
  step,
  stepArg,
  dataTableAndMaybeDocString,
  docStringAndMaybeDataTable,
  dataTable,
  docString,
  tags,
  descriptionHelper,
  description,
}

extension TokenTypeRuleType on TokenType {
  RuleType get ruleType => RuleType.values[index];
}

abstract class TokenMatcher {
  bool matchEOF(Token token);

  bool matchEmpty(Token token);

  bool matchComment(Token token);

  bool matchTagLine(Token token);

  bool matchFeatureLine(Token token);

  bool matchRuleLine(Token token);

  bool matchBackgroundLine(Token token);

  bool matchScenarioLine(Token token);

  bool matchExamplesLine(Token token);

  bool matchStepLine(Token token);

  bool matchDocStringSeparator(Token token);

  bool matchTableRow(Token token);

  bool matchLanguage(Token token);

  bool matchOther(Token token);

  void reset();
}

class Parser<T> {
  Parser(this._builder);

  final Builder<T> _builder;

  T parse(TokenScanner tokenScanner, TokenMatcher tokenMatcher) {
    _builder.reset();
    tokenMatcher.reset();

    final context = _ParserContext(
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

  void _addError(_ParserContext context, ParserException error) {
    for (final e in context.errors) {
      if (e.message == error.message) {
        return;
      }
    }
    context.errors.add(error);
    if (context.errors.length > 10) {
      throw CompositeParserException(context.errors);
    }
  }

  void _handleAstError<V>(_ParserContext context, V Function() action) =>
      _handleExternalError(context, action, null);

  V _handleExternalError<V>(
    _ParserContext context,
    V Function() action,
    V defaultValue,
  ) {
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

  void _build(_ParserContext context, Token token) =>
      _handleAstError(context, () {
        _builder.build(token);
      });

  void _startRule(_ParserContext context, RuleType ruleType) =>
      _handleAstError(context, () {
        _builder.startRule(ruleType);
      });

  void _endRule(_ParserContext context, RuleType ruleType) =>
      _handleAstError(context, () {
        _builder.endRule(ruleType);
      });

  Token _readToken(_ParserContext context) =>
      context.tokenQueue.isNotEmpty
          ? context.tokenQueue.removeFirst()
          : context.tokenScanner.read();

  bool _matchEOF(_ParserContext context, Token token) {
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchEOF(token),
      false,
    );
  }

  bool _matchEmpty(_ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchEmpty(token),
      false,
    );
  }

  bool _matchComment(_ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchComment(token),
      false,
    );
  }

  bool _matchTagLine(_ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchTagLine(token),
      false,
    );
  }

  bool _matchFeatureLine(_ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchFeatureLine(token),
      false,
    );
  }

  bool _matchRuleLine(_ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchRuleLine(token),
      false,
    );
  }

  bool _matchBackgroundLine(_ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchBackgroundLine(token),
      false,
    );
  }

  bool _matchScenarioLine(_ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchScenarioLine(token),
      false,
    );
  }

  bool _matchExamplesLine(_ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchExamplesLine(token),
      false,
    );
  }

  bool _matchStepLine(_ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchStepLine(token),
      false,
    );
  }

  bool _matchDocStringSeparator(_ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchDocStringSeparator(token),
      false,
    );
  }

  bool _matchTableRow(_ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchTableRow(token),
      false,
    );
  }

  bool _matchLanguage(_ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchLanguage(token),
      false,
    );
  }

  bool _matchOther(_ParserContext context, Token token) {
    if (token.isEof) {
      return false;
    }
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchOther(token),
      false,
    );
  }

  int _matchToken(int state, Token token, _ParserContext context) {
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
      case 51:
        newState = _matchTokenAt_51(token, context);
      case 52:
        newState = _matchTokenAt_52(token, context);
      case 53:
        newState = _matchTokenAt_53(token, context);
      case 54:
        newState = _matchTokenAt_54(token, context);
      default:
        throw StateError('Unknown state: $state');
    }
    return newState;
  }

  int _matchTokenAt_0(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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

    final expectedTokens = <String>[
      '#EOF',
      '#Language',
      '#TagLine',
      '#FeatureLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 0;
  }

  int _matchTokenAt_1(Token token, _ParserContext context) {
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

    final expectedTokens = <String>[
      '#TagLine',
      '#FeatureLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 1;
  }

  int _matchTokenAt_2(Token token, _ParserContext context) {
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

    final expectedTokens = <String>[
      '#TagLine',
      '#FeatureLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 2;
  }

  int _matchTokenAt_3(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
                _startRule(context, RuleType.description);
                _build(context, token);
          return 4;
    }
    if (_matchBackgroundLine(context, token)) {
                _endRule(context, RuleType.featureHeader);
                _startRule(context, RuleType.background);
                _build(context, token);
          return 5;
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

    final expectedTokens = <String>[
      '#EOF',
      '#Empty',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 3;
  }

  int _matchTokenAt_4(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
                _endRule(context, RuleType.description);
                _endRule(context, RuleType.featureHeader);
                _endRule(context, RuleType.feature);
                _build(context, token);
          return 42;
    }
    if (_matchComment(context, token)) {
                _build(context, token);
          return 4;
    }
    if (_matchBackgroundLine(context, token)) {
                _endRule(context, RuleType.description);
                _endRule(context, RuleType.featureHeader);
                _startRule(context, RuleType.background);
                _build(context, token);
          return 5;
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

    final expectedTokens = <String>[
      '#EOF',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 4;
  }

  int _matchTokenAt_5(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
                _endRule(context, RuleType.background);
                _endRule(context, RuleType.feature);
                _build(context, token);
          return 42;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 5;
    }
    if (_matchComment(context, token)) {
                _startRule(context, RuleType.description);
                _build(context, token);
          return 6;
    }
    if (_matchStepLine(context, token)) {
                _startRule(context, RuleType.step);
                _build(context, token);
          return 7;
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
          return 6;
    }

    final expectedTokens = <String>[
      '#EOF',
      '#Empty',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 5;
  }

  int _matchTokenAt_6(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
                _endRule(context, RuleType.description);
                _endRule(context, RuleType.background);
                _endRule(context, RuleType.feature);
                _build(context, token);
          return 42;
    }
    if (_matchComment(context, token)) {
                _build(context, token);
          return 6;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.description);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 7;
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
          return 6;
    }

    final expectedTokens = <String>[
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 6;
  }

  int _matchTokenAt_7(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
                _endRule(context, RuleType.step);
                _endRule(context, RuleType.background);
                _endRule(context, RuleType.feature);
                _build(context, token);
          return 42;
    }
    if (_matchTableRow(context, token)) {
                _startRule(context, RuleType.dataTable);
                _build(context, token);
          return 8;
    }
    if (_matchDocStringSeparator(context, token)) {
                _startRule(context, RuleType.docString);
                _build(context, token);
          return 52;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 7;
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
          return 7;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 7;
    }

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 7;
  }

  int _matchTokenAt_8(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
                _endRule(context, RuleType.dataTable);
                _endRule(context, RuleType.step);
                _endRule(context, RuleType.background);
                _endRule(context, RuleType.feature);
                _build(context, token);
          return 42;
    }
    if (_matchTableRow(context, token)) {
                _build(context, token);
          return 8;
    }
    if (_matchDocStringSeparator(context, token)) {
                _endRule(context, RuleType.dataTable);
                _startRule(context, RuleType.docString);
                _build(context, token);
          return 9;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.dataTable);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 7;
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
          return 8;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 8;
    }

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 8;
  }

  int _matchTokenAt_9(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 10;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 9;
    }

    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 9;
  }

  int _matchTokenAt_10(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 7;
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
          return 10;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 10;
    }

    final expectedTokens = <String>[
      '#EOF',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 10;
  }

  int _matchTokenAt_11(Token token, _ParserContext context) {
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

    final expectedTokens = <String>[
      '#TagLine',
      '#ScenarioLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 11;
  }

  int _matchTokenAt_12(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
                _startRule(context, RuleType.description);
                _build(context, token);
          return 13;
    }
    if (_matchStepLine(context, token)) {
                _startRule(context, RuleType.step);
                _build(context, token);
          return 14;
    }
    if (_matchTagLine(context, token)) {
          if (_lookahead_1(context, token)) {
                _startRule(context, RuleType.examplesDefinition);
                _startRule(context, RuleType.tags);
                _build(context, token);
          return 18;
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
          return 19;
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

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 12;
  }

  int _matchTokenAt_13(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
                _endRule(context, RuleType.description);
                _endRule(context, RuleType.scenario);
                _endRule(context, RuleType.scenarioDefinition);
                _endRule(context, RuleType.feature);
                _build(context, token);
          return 42;
    }
    if (_matchComment(context, token)) {
                _build(context, token);
          return 13;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.description);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 14;
    }
    if (_matchTagLine(context, token)) {
          if (_lookahead_1(context, token)) {
                _endRule(context, RuleType.description);
                _startRule(context, RuleType.examplesDefinition);
                _startRule(context, RuleType.tags);
                _build(context, token);
          return 18;
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
          return 19;
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

    final expectedTokens = <String>[
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 13;
  }

  int _matchTokenAt_14(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 15;
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
          return 14;
    }
    if (_matchTagLine(context, token)) {
          if (_lookahead_1(context, token)) {
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.examplesDefinition);
                _startRule(context, RuleType.tags);
                _build(context, token);
          return 18;
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
          return 19;
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
          return 14;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 14;
    }

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 14;
  }

  int _matchTokenAt_15(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 15;
    }
    if (_matchDocStringSeparator(context, token)) {
                _endRule(context, RuleType.dataTable);
                _startRule(context, RuleType.docString);
                _build(context, token);
          return 16;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.dataTable);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 14;
    }
    if (_matchTagLine(context, token)) {
          if (_lookahead_1(context, token)) {
                _endRule(context, RuleType.dataTable);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.examplesDefinition);
                _startRule(context, RuleType.tags);
                _build(context, token);
          return 18;
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
          return 19;
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
          return 15;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 15;
    }

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 15;
  }

  int _matchTokenAt_16(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 17;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 16;
    }

    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 16;
  }

  int _matchTokenAt_17(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 14;
    }
    if (_matchTagLine(context, token)) {
          if (_lookahead_1(context, token)) {
                _endRule(context, RuleType.docString);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.examplesDefinition);
                _startRule(context, RuleType.tags);
                _build(context, token);
          return 18;
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
          return 19;
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
          return 17;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 17;
    }

    final expectedTokens = <String>[
      '#EOF',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 17;
  }

  int _matchTokenAt_18(Token token, _ParserContext context) {
    if (_matchTagLine(context, token)) {
                _build(context, token);
          return 18;
    }
    if (_matchExamplesLine(context, token)) {
                _endRule(context, RuleType.tags);
                _startRule(context, RuleType.examples);
                _build(context, token);
          return 19;
    }
    if (_matchComment(context, token)) {
                _build(context, token);
          return 18;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 18;
    }

    final expectedTokens = <String>[
      '#TagLine',
      '#ExamplesLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 18;
  }

  int _matchTokenAt_19(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 19;
    }
    if (_matchComment(context, token)) {
                _startRule(context, RuleType.description);
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
          return 18;
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
          return 19;
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
          return 20;
    }

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 19;
  }

  int _matchTokenAt_20(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 18;
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
          return 19;
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
          return 20;
    }

    final expectedTokens = <String>[
      '#EOF',
      '#Comment',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 20;
  }

  int _matchTokenAt_21(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 18;
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
          return 19;
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

    final expectedTokens = <String>[
      '#EOF',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 21;
  }

  int _matchTokenAt_22(Token token, _ParserContext context) {
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

    final expectedTokens = <String>[
      '#TagLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 22;
  }

  int _matchTokenAt_23(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
                _startRule(context, RuleType.description);
                _build(context, token);
          return 24;
    }
    if (_matchBackgroundLine(context, token)) {
                _endRule(context, RuleType.ruleHeader);
                _startRule(context, RuleType.background);
                _build(context, token);
          return 25;
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

    final expectedTokens = <String>[
      '#EOF',
      '#Empty',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 23;
  }

  int _matchTokenAt_24(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
                _endRule(context, RuleType.description);
                _endRule(context, RuleType.ruleHeader);
                _endRule(context, RuleType.rule);
                _endRule(context, RuleType.feature);
                _build(context, token);
          return 42;
    }
    if (_matchComment(context, token)) {
                _build(context, token);
          return 24;
    }
    if (_matchBackgroundLine(context, token)) {
                _endRule(context, RuleType.description);
                _endRule(context, RuleType.ruleHeader);
                _startRule(context, RuleType.background);
                _build(context, token);
          return 25;
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

    final expectedTokens = <String>[
      '#EOF',
      '#Comment',
      '#BackgroundLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 24;
  }

  int _matchTokenAt_25(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
                _endRule(context, RuleType.background);
                _endRule(context, RuleType.rule);
                _endRule(context, RuleType.feature);
                _build(context, token);
          return 42;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 25;
    }
    if (_matchComment(context, token)) {
                _startRule(context, RuleType.description);
                _build(context, token);
          return 26;
    }
    if (_matchStepLine(context, token)) {
                _startRule(context, RuleType.step);
                _build(context, token);
          return 27;
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
          return 26;
    }

    final expectedTokens = <String>[
      '#EOF',
      '#Empty',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 25;
  }

  int _matchTokenAt_26(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
                _endRule(context, RuleType.description);
                _endRule(context, RuleType.background);
                _endRule(context, RuleType.rule);
                _endRule(context, RuleType.feature);
                _build(context, token);
          return 42;
    }
    if (_matchComment(context, token)) {
                _build(context, token);
          return 26;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.description);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 27;
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
          return 26;
    }

    final expectedTokens = <String>[
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 26;
  }

  int _matchTokenAt_27(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 28;
    }
    if (_matchDocStringSeparator(context, token)) {
                _startRule(context, RuleType.docString);
                _build(context, token);
          return 46;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 27;
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
          return 27;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 27;
    }

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 27;
  }

  int _matchTokenAt_28(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 28;
    }
    if (_matchDocStringSeparator(context, token)) {
                _endRule(context, RuleType.dataTable);
                _startRule(context, RuleType.docString);
                _build(context, token);
          return 29;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.dataTable);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 27;
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
          return 28;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 28;
    }

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 28;
  }

  int _matchTokenAt_29(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 30;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 29;
    }

    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 29;
  }

  int _matchTokenAt_30(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 27;
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
          return 30;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 30;
    }

    final expectedTokens = <String>[
      '#EOF',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 30;
  }

  int _matchTokenAt_31(Token token, _ParserContext context) {
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

    final expectedTokens = <String>[
      '#TagLine',
      '#ScenarioLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 31;
  }

  int _matchTokenAt_32(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
                _startRule(context, RuleType.description);
                _build(context, token);
          return 33;
    }
    if (_matchStepLine(context, token)) {
                _startRule(context, RuleType.step);
                _build(context, token);
          return 34;
    }
    if (_matchTagLine(context, token)) {
          if (_lookahead_1(context, token)) {
                _startRule(context, RuleType.examplesDefinition);
                _startRule(context, RuleType.tags);
                _build(context, token);
          return 38;
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
          return 39;
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

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 32;
  }

  int _matchTokenAt_33(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 33;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.description);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 34;
    }
    if (_matchTagLine(context, token)) {
          if (_lookahead_1(context, token)) {
                _endRule(context, RuleType.description);
                _startRule(context, RuleType.examplesDefinition);
                _startRule(context, RuleType.tags);
                _build(context, token);
          return 38;
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
          return 39;
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

    final expectedTokens = <String>[
      '#EOF',
      '#Comment',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 33;
  }

  int _matchTokenAt_34(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 35;
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
          return 34;
    }
    if (_matchTagLine(context, token)) {
          if (_lookahead_1(context, token)) {
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.examplesDefinition);
                _startRule(context, RuleType.tags);
                _build(context, token);
          return 38;
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
          return 39;
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
          return 34;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 34;
    }

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 34;
  }

  int _matchTokenAt_35(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 35;
    }
    if (_matchDocStringSeparator(context, token)) {
                _endRule(context, RuleType.dataTable);
                _startRule(context, RuleType.docString);
                _build(context, token);
          return 36;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.dataTable);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 34;
    }
    if (_matchTagLine(context, token)) {
          if (_lookahead_1(context, token)) {
                _endRule(context, RuleType.dataTable);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.examplesDefinition);
                _startRule(context, RuleType.tags);
                _build(context, token);
          return 38;
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
          return 39;
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
          return 35;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 35;
    }

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 35;
  }

  int _matchTokenAt_36(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 37;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 36;
    }

    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 36;
  }

  int _matchTokenAt_37(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 34;
    }
    if (_matchTagLine(context, token)) {
          if (_lookahead_1(context, token)) {
                _endRule(context, RuleType.docString);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.examplesDefinition);
                _startRule(context, RuleType.tags);
                _build(context, token);
          return 38;
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
          return 39;
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
          return 37;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 37;
    }

    final expectedTokens = <String>[
      '#EOF',
      '#StepLine',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 37;
  }

  int _matchTokenAt_38(Token token, _ParserContext context) {
    if (_matchTagLine(context, token)) {
                _build(context, token);
          return 38;
    }
    if (_matchExamplesLine(context, token)) {
                _endRule(context, RuleType.tags);
                _startRule(context, RuleType.examples);
                _build(context, token);
          return 39;
    }
    if (_matchComment(context, token)) {
                _build(context, token);
          return 38;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 38;
    }

    final expectedTokens = <String>[
      '#TagLine',
      '#ExamplesLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 38;
  }

  int _matchTokenAt_39(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 39;
    }
    if (_matchComment(context, token)) {
                _startRule(context, RuleType.description);
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
          return 38;
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
          return 39;
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
          return 40;
    }

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 39;
  }

  int _matchTokenAt_40(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 38;
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
          return 39;
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
          return 40;
    }

    final expectedTokens = <String>[
      '#EOF',
      '#Comment',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 40;
  }

  int _matchTokenAt_41(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 38;
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
          return 39;
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

    final expectedTokens = <String>[
      '#EOF',
      '#TableRow',
      '#TagLine',
      '#ExamplesLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 41;
  }

  int _matchTokenAt_43(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 44;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 43;
    }

    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 43;
  }

  int _matchTokenAt_44(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
                _endRule(context, RuleType.docString);
                _endRule(context, RuleType.step);
                _endRule(context, RuleType.scenario);
                _endRule(context, RuleType.scenarioDefinition);
                _endRule(context, RuleType.rule);
                _endRule(context, RuleType.feature);
                _build(context, token);
          return 42;
    }
    if (_matchTableRow(context, token)) {
                _endRule(context, RuleType.docString);
                _startRule(context, RuleType.dataTable);
                _build(context, token);
          return 45;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.docString);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 34;
    }
    if (_matchTagLine(context, token)) {
          if (_lookahead_1(context, token)) {
                _endRule(context, RuleType.docString);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.examplesDefinition);
                _startRule(context, RuleType.tags);
                _build(context, token);
          return 38;
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
          return 39;
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

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 44;
  }

  int _matchTokenAt_45(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 45;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.dataTable);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 34;
    }
    if (_matchTagLine(context, token)) {
          if (_lookahead_1(context, token)) {
                _endRule(context, RuleType.dataTable);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.examplesDefinition);
                _startRule(context, RuleType.tags);
                _build(context, token);
          return 38;
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
          return 39;
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
          return 45;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 45;
    }

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 45;
  }

  int _matchTokenAt_46(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 47;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 46;
    }

    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 46;
  }

  int _matchTokenAt_47(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
                _endRule(context, RuleType.docString);
                _endRule(context, RuleType.step);
                _endRule(context, RuleType.background);
                _endRule(context, RuleType.rule);
                _endRule(context, RuleType.feature);
                _build(context, token);
          return 42;
    }
    if (_matchTableRow(context, token)) {
                _endRule(context, RuleType.docString);
                _startRule(context, RuleType.dataTable);
                _build(context, token);
          return 48;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.docString);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 27;
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
          return 47;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 47;
    }

    final expectedTokens = <String>[
      '#EOF',
      '#TableRow',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 47;
  }

  int _matchTokenAt_48(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 48;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.dataTable);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 27;
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
          return 48;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 48;
    }

    final expectedTokens = <String>[
      '#EOF',
      '#TableRow',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 48;
  }

  int _matchTokenAt_49(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 50;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 49;
    }

    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 49;
  }

  int _matchTokenAt_50(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
                _endRule(context, RuleType.docString);
                _endRule(context, RuleType.step);
                _endRule(context, RuleType.scenario);
                _endRule(context, RuleType.scenarioDefinition);
                _endRule(context, RuleType.feature);
                _build(context, token);
          return 42;
    }
    if (_matchTableRow(context, token)) {
                _endRule(context, RuleType.docString);
                _startRule(context, RuleType.dataTable);
                _build(context, token);
          return 51;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.docString);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 14;
    }
    if (_matchTagLine(context, token)) {
          if (_lookahead_1(context, token)) {
                _endRule(context, RuleType.docString);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.examplesDefinition);
                _startRule(context, RuleType.tags);
                _build(context, token);
          return 18;
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
          return 19;
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
          return 50;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 50;
    }

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 50;
  }

  int _matchTokenAt_51(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
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
          return 51;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.dataTable);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 14;
    }
    if (_matchTagLine(context, token)) {
          if (_lookahead_1(context, token)) {
                _endRule(context, RuleType.dataTable);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.examplesDefinition);
                _startRule(context, RuleType.tags);
                _build(context, token);
          return 18;
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
          return 19;
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
          return 51;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 51;
    }

    final expectedTokens = <String>[
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
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 51;
  }

  int _matchTokenAt_52(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 53;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 52;
    }

    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 52;
  }

  int _matchTokenAt_53(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
                _endRule(context, RuleType.docString);
                _endRule(context, RuleType.step);
                _endRule(context, RuleType.background);
                _endRule(context, RuleType.feature);
                _build(context, token);
          return 42;
    }
    if (_matchTableRow(context, token)) {
                _endRule(context, RuleType.docString);
                _startRule(context, RuleType.dataTable);
                _build(context, token);
          return 54;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.docString);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 7;
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
          return 53;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 53;
    }

    final expectedTokens = <String>[
      '#EOF',
      '#TableRow',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 53;
  }

  int _matchTokenAt_54(Token token, _ParserContext context) {
    if (_matchEOF(context, token)) {
                _endRule(context, RuleType.dataTable);
                _endRule(context, RuleType.step);
                _endRule(context, RuleType.background);
                _endRule(context, RuleType.feature);
                _build(context, token);
          return 42;
    }
    if (_matchTableRow(context, token)) {
                _build(context, token);
          return 54;
    }
    if (_matchStepLine(context, token)) {
                _endRule(context, RuleType.dataTable);
                _endRule(context, RuleType.step);
                _startRule(context, RuleType.step);
                _build(context, token);
          return 7;
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
          return 54;
    }
    if (_matchEmpty(context, token)) {
                _build(context, token);
          return 54;
    }

    final expectedTokens = <String>[
      '#EOF',
      '#TableRow',
      '#StepLine',
      '#TagLine',
      '#ScenarioLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    _addError(context, error);
    return 54;
  }

  bool _lookahead_0(_ParserContext context, Token currentToken) {
    Token token;
    final queue = Queue<Token>();
    var match = false;
    do {
      token = _readToken(context);
      queue.add(token);

      if (false
              || _matchScenarioLine(context, token)
) {
        match = true;
        break;
      }
    } while (false
            || _matchEmpty(context, token)
            || _matchComment(context, token)
            || _matchTagLine(context, token)
);

    context.tokenQueue.addAll(queue);

    return match;
  }

  bool _lookahead_1(_ParserContext context, Token currentToken) {
    Token token;
    final queue = Queue<Token>();
    var match = false;
    do {
      token = _readToken(context);
      queue.add(token);

      if (false
              || _matchExamplesLine(context, token)
) {
        match = true;
        break;
      }
    } while (false
            || _matchEmpty(context, token)
            || _matchComment(context, token)
            || _matchTagLine(context, token)
);

    context.tokenQueue.addAll(queue);

    return match;
  }
}

final class _ParserContext {
  _ParserContext(
    this.tokenScanner,
    this.tokenMatcher,
    this.tokenQueue,
    this.errors,
  );

  final TokenScanner tokenScanner;
  final TokenMatcher tokenMatcher;
  final Queue<Token> tokenQueue;
  final List<ParserException> errors;
}
