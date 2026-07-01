import 'package:gherkin/core.dart';
import 'package:gherkin/extensions.dart';

import 'package:gherkin/src/language/gherkin_language_keywords.dart';

/// A Gherkin dialect: the set of localized keywords for a single language.
abstract class IGherkinDialect implements INullSafetyObject {
  /// A sentinel dialect with no language and no keywords.
  static const empty = _EmptyGherkinDialect();

  /// The IETF language tag of this dialect (for example `en` or `fr`).
  String get language;

  /// The raw keyword definitions backing this dialect.
  GherkinLanguageKeywords get keywords;

  /// The keywords that introduce a `Feature`.
  List<String> get featureKeywords;

  /// The English name of the language (for example `English`).
  String get name;

  /// The native name of the language (for example `français`).
  String get nativeName;

  /// The keywords that introduce a `Rule`.
  List<String> get ruleKeywords;

  /// The keywords that introduce a `Scenario`.
  List<String> get scenarioKeywords;

  /// The keywords that introduce a `Scenario Outline`.
  List<String> get scenarioOutlineKeywords;

  /// All step keywords, regardless of their semantic type.
  List<String> get stepKeywords;

  /// The keywords that introduce a `Background`.
  List<String> get backgroundKeywords;

  /// The keywords that introduce an `Examples` block.
  List<String> get examplesKeywords;

  /// The keywords that introduce a `Given` step.
  List<String> get givenStepKeywords;

  /// The keywords that introduce a `When` step.
  List<String> get whenStepKeywords;

  /// The keywords that introduce a `Then` step.
  List<String> get thenStepKeywords;

  /// The keywords that introduce an `And` step.
  List<String> get andStepKeywords;

  /// The keywords that introduce a `But` step.
  List<String> get butStepKeywords;
}

/// Convenience implementation of an invalid [IGherkinDialect] instance.
class _EmptyGherkinDialect with INullSafetyObject implements IGherkinDialect {
  const _EmptyGherkinDialect();

  @override
  List<String> get andStepKeywords => [];

  @override
  List<String> get backgroundKeywords => [];

  @override
  List<String> get butStepKeywords => [];

  @override
  List<String> get examplesKeywords => [];

  @override
  List<String> get featureKeywords => [];

  @override
  List<String> get givenStepKeywords => [];

  @override
  GherkinLanguageKeywords get keywords => GherkinLanguageKeywords.empty;

  @override
  String get language => Strings.empty;

  @override
  String get name => Strings.empty;

  @override
  String get nativeName => Strings.empty;

  @override
  List<String> get ruleKeywords => [];

  @override
  List<String> get scenarioKeywords => [];

  @override
  List<String> get scenarioOutlineKeywords => [];

  @override
  List<String> get stepKeywords => [];

  @override
  List<String> get thenStepKeywords => [];

  @override
  List<String> get whenStepKeywords => [];

  @override
  bool get isEmpty => true;
}
