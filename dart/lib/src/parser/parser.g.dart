// GENERATED FILE - DO NOT EDIT.
//
// This file was generated from `gherkin-dart.razor` by
// [Berp](https://github.com/gasparnagy/berp) using the shared
// `../gherkin.berp` grammar. Run `make generate` to regenerate it.
//
// The `TokenType` and `RuleType` enums below are generated here from the
// grammar. `Builder`, `TokenMatcher`, and `TokenScanner` live in hand-written
// sibling files; `_ParserContext` is generated below (library-private).
// dart format off
import 'dart:collection';

import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/builder.dart';
import 'package:cucumber_gherkin/src/parser/token_matcher.dart';
import 'package:cucumber_gherkin/src/parser/token_scanner.dart';

/// The lexical token types produced while scanning a Gherkin document.
enum TokenType {
  /// No token; the initial/sentinel value.
  none,

  /// End of file.
  eof,

  /// A blank (whitespace-only) line.
  empty,

  /// A comment line (starting with `#`).
  comment,

  /// A line containing one or more tags.
  tagLine,

  /// A `Feature:` line.
  featureLine,

  /// A `Rule:` line.
  ruleLine,

  /// A `Background:` line.
  backgroundLine,

  /// A `Scenario:` or `Scenario Outline:` line.
  scenarioLine,

  /// An `Examples:` line.
  examplesLine,

  /// A step line (`Given`/`When`/`Then`/`And`/`But`).
  stepLine,

  /// A doc string delimiter (`"""` or ` ``` `).
  docStringSeparator,

  /// A data/examples table row.
  tableRow,

  /// A `# language:` header line.
  language,

  /// Any other line (free text or description).
  other,
}

/// The grammar rules recognized by the Gherkin parser.
///
/// The first group mirrors the lexical [TokenType]s one-to-one (see
/// [TokenType.ruleType]); the remaining values are the structural production
/// rules of the Gherkin grammar.
enum RuleType {
  /// No rule; the initial/sentinel value.
  none,

  /// End-of-file token rule (`#EOF`).
  eof,

  /// Blank line token rule (`#Empty`).
  empty,

  /// Comment line token rule (`#Comment`).
  comment,

  /// Tag line token rule (`#TagLine`).
  tagLine,

  /// `Feature:` line token rule (`#FeatureLine`).
  featureLine,

  /// `Rule:` line token rule (`#RuleLine`).
  ruleLine,

  /// `Background:` line token rule (`#BackgroundLine`).
  backgroundLine,

  /// `Scenario:`/`Scenario Outline:` line token rule (`#ScenarioLine`).
  scenarioLine,

  /// `Examples:` line token rule (`#ExamplesLine`).
  examplesLine,

  /// Step line token rule (`#StepLine`).
  stepLine,

  /// Doc string delimiter token rule (`#DocStringSeparator`).
  docStringSeparator,

  /// Table row token rule (`#TableRow`).
  tableRow,

  /// `# language:` header token rule (`#Language`).
  language,

  /// Any other (description/free text) token rule (`#Other`).
  other,

  /// The whole document: `GherkinDocument := Feature?`.
  gherkinDocument,

  /// A feature:
  /// `Feature := FeatureHeader Background? ScenarioDefinition* Rule*`.
  feature,

  /// A feature header:
  /// `FeatureHeader := #Language? Tags? #FeatureLine DescriptionHelper`.
  featureHeader,

  /// A rule: `Rule := RuleHeader Background? ScenarioDefinition*`.
  rule,

  /// A rule header: `RuleHeader := Tags? #RuleLine DescriptionHelper`.
  ruleHeader,

  /// A background: `Background := #BackgroundLine DescriptionHelper Step*`.
  background,

  /// A (optionally tagged) scenario: `ScenarioDefinition := Tags? Scenario`.
  scenarioDefinition,

  /// A scenario:
  /// `Scenario := #ScenarioLine DescriptionHelper Step* ExamplesDefinition*`.
  scenario,

  /// A (optionally tagged) examples block:
  /// `ExamplesDefinition := Tags? Examples`.
  examplesDefinition,

  /// An examples block:
  /// `Examples := #ExamplesLine DescriptionHelper ExamplesTable?`.
  examples,

  /// An examples table: `ExamplesTable := #TableRow #TableRow*`.
  examplesTable,

  /// A step: `Step := #StepLine StepArg?`.
  step,

  /// A step argument: `StepArg := (DataTable | DocString)`.
  stepArg,

  /// Grammar rule `dataTableAndMaybeDocString`.
  dataTableAndMaybeDocString,

  /// Grammar rule `docStringAndMaybeDataTable`.
  docStringAndMaybeDataTable,

  /// A data table: `DataTable := #TableRow+`.
  dataTable,

  /// A doc string:
  /// `DocString := #DocStringSeparator #Other* #DocStringSeparator`.
  docString,

  /// One or more tag lines: `Tags := #TagLine+`.
  tags,

  /// A description helper:
  /// `DescriptionHelper := #Empty* Description?`.
  descriptionHelper,

  /// Free-text description: `Description := (#Other | #Comment)+`.
  description,
}

/// The [RuleType] that corresponds to this lexical token type.
///
/// The leading [RuleType] values mirror [TokenType] in declaration order
/// (both are generated from the same grammar), so the mapping is by index.
extension TokenTypeRuleType on TokenType {
  RuleType get ruleType => RuleType.values[index];
}

/// A recursive-descent Gherkin parser driven by a Berp-generated state machine.
///
/// The parser reads [Token]s from a [TokenScanner], classifies them with a
/// [TokenMatcher], and feeds the recognized grammar rules to a [Builder] of
/// type [T], which assembles the final result returned by [parse].
class Parser<T> {
  /// Creates a parser that emits its result through the given [Builder].
  Parser(this._builder);

  final Builder<T> _builder;

  /// Whether parsing should throw on the first error instead of collecting
  /// every error encountered while scanning the document.
  bool stopAtFirstError = false;

  /// Parses the tokens produced by [tokenScanner], using [tokenMatcher] to
  /// classify each token, and returns the assembled result of type [T].
  ///
  /// Throws a [CompositeParserException] if one or more parse errors are
  /// encountered.
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
    // Deduplicate by message. Each message already carries its
    // `(line:column): ` position prefix, so identical messages describe the
    // same error at the same location.
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

  bool _matchEof(_ParserContext context, Token token) {
    return _handleExternalError(
      context,
      () => context.tokenMatcher.matchEof(token),
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

  // Start
  int _matchTokenAt_0(Token token, _ParserContext context) {
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 0;
  }

  // GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0
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

    token.detach();
    final expectedTokens = <String>[
      '#TagLine',
      '#FeatureLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 1;
  }

  // GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0
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

    token.detach();
    final expectedTokens = <String>[
      '#TagLine',
      '#FeatureLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 2;
  }

  // GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0
  int _matchTokenAt_3(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 3;
  }

  // GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
  int _matchTokenAt_4(Token token, _ParserContext context) {
    if (_matchEof(context, token)) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 4;
  }

  // GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0
  int _matchTokenAt_5(Token token, _ParserContext context) {
    if (_matchEof(context, token)) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 5;
  }

  // GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
  int _matchTokenAt_6(Token token, _ParserContext context) {
    if (_matchEof(context, token)) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 6;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0
  int _matchTokenAt_7(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 7;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
  int _matchTokenAt_8(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 8;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
  int _matchTokenAt_9(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 10;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 9;
    }

    token.detach();
    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 9;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
  int _matchTokenAt_10(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 10;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0
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

    token.detach();
    final expectedTokens = <String>[
      '#TagLine',
      '#ScenarioLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 11;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
  int _matchTokenAt_12(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 12;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
  int _matchTokenAt_13(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 13;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
  int _matchTokenAt_14(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 14;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
  int _matchTokenAt_15(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 15;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
  int _matchTokenAt_16(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 17;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 16;
    }

    token.detach();
    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 16;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
  int _matchTokenAt_17(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 17;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
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

    token.detach();
    final expectedTokens = <String>[
      '#TagLine',
      '#ExamplesLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 18;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
  int _matchTokenAt_19(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 19;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
  int _matchTokenAt_20(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 20;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
  int _matchTokenAt_21(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 21;
  }

  // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0
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

    token.detach();
    final expectedTokens = <String>[
      '#TagLine',
      '#RuleLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 22;
  }

  // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>#RuleLine:0
  int _matchTokenAt_23(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 23;
  }

  // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
  int _matchTokenAt_24(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 24;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0
  int _matchTokenAt_25(Token token, _ParserContext context) {
    if (_matchEof(context, token)) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 25;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
  int _matchTokenAt_26(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 26;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0
  int _matchTokenAt_27(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 27;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
  int _matchTokenAt_28(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 28;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
  int _matchTokenAt_29(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 30;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 29;
    }

    token.detach();
    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 29;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
  int _matchTokenAt_30(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 30;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0
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

    token.detach();
    final expectedTokens = <String>[
      '#TagLine',
      '#ScenarioLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 31;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
  int _matchTokenAt_32(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 32;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
  int _matchTokenAt_33(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 33;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
  int _matchTokenAt_34(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 34;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
  int _matchTokenAt_35(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 35;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
  int _matchTokenAt_36(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 37;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 36;
    }

    token.detach();
    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 36;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
  int _matchTokenAt_37(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 37;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
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

    token.detach();
    final expectedTokens = <String>[
      '#TagLine',
      '#ExamplesLine',
      '#Comment',
      '#Empty',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 38;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
  int _matchTokenAt_39(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 39;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
  int _matchTokenAt_40(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 40;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
  int _matchTokenAt_41(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 41;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
  int _matchTokenAt_43(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 44;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 43;
    }

    token.detach();
    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 43;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
  int _matchTokenAt_44(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 44;
  }

  // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
  int _matchTokenAt_45(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 45;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
  int _matchTokenAt_46(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 47;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 46;
    }

    token.detach();
    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 46;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
  int _matchTokenAt_47(Token token, _ParserContext context) {
    if (_matchEof(context, token)) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 47;
  }

  // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
  int _matchTokenAt_48(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 48;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
  int _matchTokenAt_49(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 50;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 49;
    }

    token.detach();
    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 49;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
  int _matchTokenAt_50(Token token, _ParserContext context) {
    if (_matchEof(context, token)) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 50;
  }

  // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
  int _matchTokenAt_51(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 51;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
  int _matchTokenAt_52(Token token, _ParserContext context) {
    if (_matchDocStringSeparator(context, token)) {
                _build(context, token);
          return 53;
    }
    if (_matchOther(context, token)) {
                _build(context, token);
          return 52;
    }

    token.detach();
    final expectedTokens = <String>[
      '#DocStringSeparator',
      '#Other',
    ];
    final error = token.isEof
        ? UnexpectedEofException(token, expectedTokens)
        : UnexpectedTokenException(token, expectedTokens);

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 52;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
  int _matchTokenAt_53(Token token, _ParserContext context) {
    if (_matchEof(context, token)) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 53;
  }

  // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
  int _matchTokenAt_54(Token token, _ParserContext context) {
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

    token.detach();
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

    if (stopAtFirstError) {
      throw error;
    }

    _addError(context, error);
    return 54;
  }

  bool _lookahead_0(_ParserContext context, Token currentToken) {
    currentToken.detach();
    Token token;
    final queue = Queue<Token>();
    var match = false;
    do {
      token = _readToken(context)..detach();
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
    currentToken.detach();
    Token token;
    final queue = Queue<Token>();
    var match = false;
    do {
      token = _readToken(context)..detach();
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

/// Mutable state for a single [Parser.parse] run.
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
