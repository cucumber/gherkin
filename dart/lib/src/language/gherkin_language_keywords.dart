class GherkinLanguageKeywords {
  const GherkinLanguageKeywords(
    this.name,
    this.native,
    this.feature,
    this.rule,
    this.background,
    this.scenario,
    this.scenarioOutline,
    this.examples,
    this.given,
    this.when,
    this.then,
    this.and,
    this.but,
  );

  final String name;

  final String native;

  final List<String> feature;

  final List<String> rule;

  final List<String> background;

  final List<String> scenario;

  final List<String> scenarioOutline;

  final List<String> examples;

  final List<String> given;

  final List<String> when;

  final List<String> then;

  final List<String> and;

  final List<String> but;
}
