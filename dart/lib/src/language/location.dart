import 'package:gherkin/core.dart';
import 'package:gherkin/extensions.dart';

/// A one-based position (line and column) within a source document.
class Location implements INullSafetyObject {
  /// Creates a location at the given [line] and [column].
  const Location(this.line, this.column);

  /// The one-based line number.
  final int line;

  /// The one-based column number.
  final int column;

  /// A sentinel location representing an invalid/absent position.
  static const empty = _InvalidLocation();

  @override
  bool get isEmpty => false;

  @override
  bool get isNotEmpty => !isEmpty;
}

/// Convenience implementation of an invalid [Location] instance.
class _InvalidLocation extends Location {
  const _InvalidLocation() : super(Int.min, Int.min);

  @override
  bool get isEmpty => true;
}
