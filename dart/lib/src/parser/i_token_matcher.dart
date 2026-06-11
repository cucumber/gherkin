import 'package:gherkin/language.dart';

abstract class ITokenMatcher {
  bool matchEof(Token token);
  bool matchEmpty(Token token);
  bool matchComment(Token token);
  bool matchTagLine(Token token);
  bool matchFeatureLine(Token token);
  bool matchRuleLine(Token token);
  bool matchBackgroundLine(Token token);
  bool matchScenarioLine(Token token);
  bool matchExamplesLine(Token token);
  bool matchStepLine(Token token);
  bool matchDocStringSeparator(Token token);
  bool matchTableRow(Token token);
  bool matchLanguage(Token token);
  bool matchOther(Token token);
  void reset();
}
