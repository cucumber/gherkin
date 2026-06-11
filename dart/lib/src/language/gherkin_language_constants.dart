/// Punctuation and delimiter constants shared by the Gherkin scanners.
class GherkinLanguageConstants {
  /// The prefix that introduces a tag (`@`).
  static const tagPrefix = '@';

  /// The prefix that introduces a comment line (`#`).
  static const commentPrefix = '#';

  /// The separator between a keyword and its title (`:`).
  static const titleKeywordSeparator = ':';

  /// The character that separates table cells (`|`).
  static const tableCellSeparator = '|';

  /// The escape character used inside table cells (`\`).
  static const tableCellEscapeChar = r'\';

  /// The escaped-newline indicator inside table cells (`n`, as in `\n`).
  static const tableCellNewLineEscape = 'n';

  /// The default doc string delimiter (`"""`).
  static const docStringSeparator = '"""';

  /// The alternative doc string delimiter (` ``` `).
  static const docStringAlternativeSeparator = '```';
}
