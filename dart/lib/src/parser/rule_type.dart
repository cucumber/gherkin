/// The grammar rules recognized by the Gherkin parser.
///
/// The first group mirrors the lexical `TokenType`s one-to-one (the explicit
/// mapping lives in `TokenTypeExtension.toRuleType`); the remaining values are
/// the structural production rules of the Gherkin grammar.
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

  /// A rule header: `RuleHeader := #RuleLine DescriptionHelper`.
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
