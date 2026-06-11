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
