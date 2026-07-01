import 'package:gherkin/core.dart';
import 'package:gherkin/src/language/gherkin_language_keywords.dart';
import 'package:gherkin/src/language/i_gherkin_dialect.dart';

/// The concrete [IGherkinDialect] backed by a set of
/// [GherkinLanguageKeywords].
class GherkinDialect with INullSafetyObject implements IGherkinDialect {
  /// Creates a dialect for [_language] using the given [_keywords].
  GherkinDialect(this._language, this._keywords);
  final String _language;
  final GherkinLanguageKeywords _keywords;

  @override
  GherkinLanguageKeywords get keywords => _keywords;

  @override
  String get language => _language;

  @override
  List<String> get featureKeywords => keywords.feature;

  @override
  String get name => keywords.name;

  @override
  String get nativeName => keywords.native;

  @override
  List<String> get ruleKeywords => keywords.rule;

  @override
  List<String> get scenarioKeywords => keywords.scenario;

  @override
  List<String> get scenarioOutlineKeywords => keywords.scenarioOutline;

  @override
  List<String> get stepKeywords =>
      <String>{
        ...givenStepKeywords,
        ...whenStepKeywords,
        ...thenStepKeywords,
        ...andStepKeywords,
        ...butStepKeywords,
      }.toList();

  @override
  List<String> get backgroundKeywords => keywords.background;

  @override
  List<String> get examplesKeywords => keywords.examples;

  @override
  List<String> get givenStepKeywords => keywords.given;

  @override
  List<String> get whenStepKeywords => keywords.when;

  @override
  List<String> get thenStepKeywords => keywords.then;

  @override
  List<String> get andStepKeywords => keywords.and;

  @override
  List<String> get butStepKeywords => keywords.but;

  @override
  bool get isEmpty => false;
}
