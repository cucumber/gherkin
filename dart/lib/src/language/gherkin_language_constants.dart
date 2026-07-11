/// Punctuation and delimiter constants used while scanning Gherkin lines.
library;

/// The prefix that introduces a tag (`@`).
const tagPrefix = '@';

/// The prefix that introduces a comment line (`#`).
const commentPrefix = '#';

/// The separator between a keyword and its title (`:`).
const titleKeywordSeparator = ':';

/// The character that separates table cells (`|`).
const tableCellSeparator = '|';

/// The escape character used inside table cells (`\`).
const tableCellEscapeChar = r'\';

/// The escaped-newline indicator inside table cells (`n`, as in `\n`).
const tableCellNewLineEscape = 'n';

/// The default doc string delimiter (`"""`).
const docStringSeparator = '"""';

/// The alternative doc string delimiter (` ``` `).
const docStringAlternativeSeparator = '```';
