import 'package:cucumber_gherkin/src/language/token.dart';

/// A source of [Token]s consumed by the parser.
///
/// Scanners are stateful: each [read] advances over the input and returns a
/// [Token] for the next source line, or an EOF token when input is exhausted.
abstract class TokenScanner {
  /// Reads and returns the next [Token] from the underlying source.
  Token read();
}
