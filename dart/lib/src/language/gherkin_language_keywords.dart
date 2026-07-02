/// The localized Gherkin keywords for a single language, as defined in
/// `gherkin-languages.json`.
class GherkinLanguageKeywords {
  /// Creates a set of keywords from explicit values.
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

  /// A sentinel value with an empty name and no keywords.
  static const GherkinLanguageKeywords empty = GherkinLanguageKeywords(
    '',
    '',
    [],
    [],
    [],
    [],
    [],
    [],
    [],
    [],
    [],
    [],
    [],
  );

  /// The English name of the language (for example `English`).
  final String name;

  /// The native name of the language (for example `English`).
  final String native;

  /// The keywords that introduce a `Feature`.
  final List<String> feature;

  /// The keywords that introduce a `Rule`.
  final List<String> rule;

  /// The keywords that introduce a `Background`.
  final List<String> background;

  /// The keywords that introduce a `Scenario`.
  final List<String> scenario;

  /// The keywords that introduce a `Scenario Outline`.
  final List<String> scenarioOutline;

  /// The keywords that introduce an `Examples` block.
  final List<String> examples;

  /// The keywords that introduce a `Given` step.
  final List<String> given;

  /// The keywords that introduce a `When` step.
  final List<String> when;

  /// The keywords that introduce a `Then` step.
  final List<String> then;

  /// The keywords that introduce an `And` step.
  final List<String> and;

  /// The keywords that introduce a `But` step.
  final List<String> but;
}
