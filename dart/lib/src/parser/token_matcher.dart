import 'package:cucumber_gherkin/src/language/token.dart';

/// Classifies scanned [Token]s, setting their matched type and metadata.
///
/// Each `match*` method returns whether the token matches; on success the
/// token is populated with the matched details.
abstract class TokenMatcher {
  /// Matches the end-of-file token.
  bool matchEof(Token token);

  /// Matches a blank line.
  bool matchEmpty(Token token);

  /// Matches a comment line.
  bool matchComment(Token token);

  /// Matches a tag line.
  bool matchTagLine(Token token);

  /// Matches a `Feature:` line.
  bool matchFeatureLine(Token token);

  /// Matches a `Rule:` line.
  bool matchRuleLine(Token token);

  /// Matches a `Background:` line.
  bool matchBackgroundLine(Token token);

  /// Matches a `Scenario:` or `Scenario Outline:` line.
  bool matchScenarioLine(Token token);

  /// Matches an `Examples:` line.
  bool matchExamplesLine(Token token);

  /// Matches a step line.
  bool matchStepLine(Token token);

  /// Matches a doc string delimiter line.
  bool matchDocStringSeparator(Token token);

  /// Matches a table row.
  bool matchTableRow(Token token);

  /// Matches a language header line (`# language: …`).
  bool matchLanguage(Token token);

  /// Matches any other (free text/description) line.
  bool matchOther(Token token);

  /// Resets the matcher to its initial state for reuse.
  void reset();
}
