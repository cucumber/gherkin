enum RuleType {
  none,
  // ignore: unused_field
  _eof, // #EOF
  // ignore: unused_field
  _empty, // #Empty
  // ignore: unused_field
  _comment, // #Comment
  // ignore: unused_field
  _tagLine, // #TagLine
  // ignore: unused_field
  _featureLine, // #FeatureLine
  // ignore: unused_field
  _ruleLine, // #RuleLine
  // ignore: unused_field
  _backgroundLine, // #BackgroundLine
  // ignore: unused_field
  _scenarioLine, // #ScenarioLine
  // ignore: unused_field
  _examplesLine, // #ExamplesLine
  // ignore: unused_field
  _stepLine, // #StepLine
  // ignore: unused_field
  _docStringSeparator, // #DocStringSeparator
  // ignore: unused_field
  _tableRow, // #TableRow
  // ignore: unused_field
  _language, // #Language
  // ignore: unused_field
  _other, // #Other
  gherkinDocument, // GherkinDocument! := Feature?
  feature, // Feature! := FeatureHeader Background? ScenarioDefinition* Rule*
  featureHeader, // FeatureHeader! := #Language? Tags? #FeatureLine DescriptionHelper
  rule, // Rule! := RuleHeader Background? ScenarioDefinition*
  ruleHeader, // RuleHeader! := #RuleLine DescriptionHelper
  background, // Background! := #BackgroundLine DescriptionHelper Step*
  scenarioDefinition, // ScenarioDefinition! := Tags? Scenario
  scenario, // Scenario! := #ScenarioLine DescriptionHelper Step* ExamplesDefinition*
  examplesDefinition, // ExamplesDefinition! [#Empty|#Comment|#TagLine->#ExamplesLine] := Tags? Examples
  examples, // Examples! := #ExamplesLine DescriptionHelper ExamplesTable?
  examplesTable, // ExamplesTable! := #TableRow #TableRow*
  step, // Step! := #StepLine StepArg?
  stepArg, // StepArg := (DataTable | DocString)
  dataTable, // DataTable! := #TableRow+
  docString, // DocString! := #DocStringSeparator #Other* #DocStringSeparator
  tags, // Tags! := #TagLine+
  descriptionHelper, // DescriptionHelper := #Empty* Description? #Comment*
  description, // Description! := #Other+
}
