import 'package:gherkin/core.dart';

/// Placeholder builder result used by the token formatter, which produces its
/// output as a side effect rather than via the parser's return value.
class NoOpResult with INullSafetyObject {
  @override
  bool get isEmpty => false;
}
