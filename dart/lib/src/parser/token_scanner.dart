import 'package:cucumber_gherkin/src/parser/token.dart';

/// Reads [Token] values in source order.
abstract class TokenScanner {
  /// The next token, including the end-of-file token after the last line.
  Token read();
}
