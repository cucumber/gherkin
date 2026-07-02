import 'package:cucumber_gherkin/src/language/gherkin_language_keywords.dart';

/// A Gherkin dialect: the set of localized keywords for a single language,
/// backed by a set of [GherkinLanguageKeywords].
class GherkinDialect {
  /// Creates a dialect for [_language] using the given [_keywords].
  GherkinDialect(this._language, this._keywords);

  final String _language;
  final GherkinLanguageKeywords _keywords;

  /// The raw keyword definitions backing this dialect.
  GherkinLanguageKeywords get keywords => _keywords;

  /// The IETF language tag of this dialect (for example `en` or `fr`).
  String get language => _language;

  /// The keywords that introduce a `Feature`.
  List<String> get featureKeywords => keywords.feature;

  /// The English name of the language (for example `English`).
  String get name => keywords.name;

  /// The native name of the language (for example `français`).
  String get nativeName => keywords.native;

  /// The keywords that introduce a `Rule`.
  List<String> get ruleKeywords => keywords.rule;

  /// The keywords that introduce a `Scenario`.
  List<String> get scenarioKeywords => keywords.scenario;

  /// The keywords that introduce a `Scenario Outline`.
  List<String> get scenarioOutlineKeywords => keywords.scenarioOutline;

  /// All step keywords, regardless of their semantic type.
  ///
  /// Computed once on first access and cached for subsequent reads.
  late final List<String> stepKeywords =
      <String>{
        ...givenStepKeywords,
        ...whenStepKeywords,
        ...thenStepKeywords,
        ...andStepKeywords,
        ...butStepKeywords,
      }.toList();

  /// [stepKeywords] sorted by descending length, so that the longest matching
  /// keyword is tried first (for example matching `* ` after `Given `).
  ///
  /// The order is dialect-invariant, so it is computed once on first access and
  /// cached for subsequent reads rather than re-sorted on every step line.
  late final List<String> stepKeywordsByLengthDesc = List<String>.of(
    stepKeywords,
  )..sort((a, b) => b.length - a.length);

  /// The keywords that introduce a `Background`.
  List<String> get backgroundKeywords => keywords.background;

  /// The keywords that introduce an `Examples` block.
  List<String> get examplesKeywords => keywords.examples;

  /// The keywords that introduce a `Given` step.
  List<String> get givenStepKeywords => keywords.given;

  /// The keywords that introduce a `When` step.
  List<String> get whenStepKeywords => keywords.when;

  /// The keywords that introduce a `Then` step.
  List<String> get thenStepKeywords => keywords.then;

  /// The keywords that introduce an `And` step.
  List<String> get andStepKeywords => keywords.and;

  /// The keywords that introduce a `But` step.
  List<String> get butStepKeywords => keywords.but;
}
