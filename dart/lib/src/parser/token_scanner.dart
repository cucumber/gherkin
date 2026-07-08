import 'package:cucumber_gherkin/src/language/token.dart';

/// A source of [Token]s consumed by the parser.
///
/// Scanners are stateful: each call to [read] advances over the input and
/// returns the next line as a [Token].
abstract class TokenScanner {
  /// Reads and returns the next [Token] from the underlying source.
  Token read();
}
