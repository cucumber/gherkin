import 'package:meta/meta.dart';
import 'package:uuid/uuid.dart';

/// Generates the ids assigned to emitted Cucumber messages.
abstract class IdGenerator {
  /// Returns the next id.
  String newId();

  /// A shared [Incrementing] generator producing predictable, sequential ids.
  static final IdGenerator incrementingGenerator = Incrementing();

  /// Returns a **new** [Incrementing] instance each time; safe for per-test
  /// use.
  @visibleForTesting
  static IdGenerator get freshIncrementingGenerator => Incrementing();

  /// A shared [UUID] generator producing random UUIDs.
  static final IdGenerator uuidGenerator = UUID();
}

/// An [IdGenerator] that produces random version-1 UUIDs.
class UUID implements IdGenerator {
  final Uuid _uuid = const Uuid();

  @override
  String newId() => _uuid.v1();
}

/// An [IdGenerator] that produces sequential ids starting at `0`.
class Incrementing implements IdGenerator {
  int _next = -1;

  @override
  String newId() {
    _next++;
    return _next.toString();
  }
}
