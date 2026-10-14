/// Keywords for one Gherkin dialect.
class GherkinLanguageKeywords {
  /// Creates a dialect keyword set.
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

  /// The dialect identifier, such as `en`.
  final String name;

  /// The language name written in that language.
  final String native;

  /// Keywords that start a feature.
  final List<String> feature;

  /// Keywords that start a rule.
  final List<String> rule;

  /// Keywords that start a background.
  final List<String> background;

  /// Keywords that start a scenario.
  final List<String> scenario;

  /// Keywords that start a scenario outline.
  final List<String> scenarioOutline;

  /// Keywords that start an examples block.
  final List<String> examples;

  /// Step keywords equivalent to `Given`.
  final List<String> given;

  /// Step keywords equivalent to `When`.
  final List<String> when;

  /// Step keywords equivalent to `Then`.
  final List<String> then;

  /// Step keywords equivalent to `And`.
  final List<String> and;

  /// Step keywords equivalent to `But`.
  final List<String> but;
}
