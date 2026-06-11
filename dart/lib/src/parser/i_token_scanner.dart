import 'package:gherkin/language.dart';

/// A source of [Token]s consumed by the parser.
///
/// Scanners are stateful: each call to [read] advances over the input and
/// returns the next line as a [Token]. This contract has multiple
/// implementations (for example `StringTokenScanner` and `FileTokenScanner`),
/// so it is modelled as an interface rather than a standalone function.
// ignore: one_member_abstracts
abstract class ITokenScanner {
  /// Reads and returns the next [Token] from the underlying source.
  Token read();
}
