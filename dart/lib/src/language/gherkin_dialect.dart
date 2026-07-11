import 'package:cucumber_gherkin/src/language/gherkin_language_keywords.dart';

/// A Gherkin dialect: the set of localized keywords for a single language,
/// backed by a set of [GherkinLanguageKeywords].
class GherkinDialect {
  /// Creates a dialect for [_language] using the given [_keywords].
  GherkinDialect(this._language, this._keywords);

  final String _language;
  final GherkinLanguageKeywords _keywords;

  /// The IETF language tag of this dialect (for example `en` or `fr`).
  String get language => _language;

  /// The keywords that introduce a `Feature`.
  List<String> get featureKeywords => _keywords.feature;

  /// The keywords that introduce a `Rule`.
  List<String> get ruleKeywords => _keywords.rule;

  /// The keywords that introduce a `Scenario`.
  List<String> get scenarioKeywords => _keywords.scenario;

  /// The keywords that introduce a `Scenario Outline`.
  List<String> get scenarioOutlineKeywords => _keywords.scenarioOutline;

  /// All step keywords, regardless of their semantic type.
  late final List<String> stepKeywords =
      <String>{
        ...givenStepKeywords,
        ...whenStepKeywords,
        ...thenStepKeywords,
        ...andStepKeywords,
        ...butStepKeywords,
      }.toList();

  /// [stepKeywords] sorted by descending length so the longest match wins.
  late final List<String> stepKeywordsByLengthDesc = List<String>.of(
    stepKeywords,
  )..sort((a, b) => b.length - a.length);

  /// The keywords that introduce a `Background`.
  List<String> get backgroundKeywords => _keywords.background;

  /// The keywords that introduce an `Examples` block.
  List<String> get examplesKeywords => _keywords.examples;

  /// The keywords that introduce a `Given` step.
  List<String> get givenStepKeywords => _keywords.given;

  /// The keywords that introduce a `When` step.
  List<String> get whenStepKeywords => _keywords.when;

  /// The keywords that introduce a `Then` step.
  List<String> get thenStepKeywords => _keywords.then;

  /// The keywords that introduce an `And` step.
  List<String> get andStepKeywords => _keywords.and;

  /// The keywords that introduce a `But` step.
  List<String> get butStepKeywords => _keywords.but;
}
