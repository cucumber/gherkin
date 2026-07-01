import 'dart:math';

import 'package:meta/meta.dart';

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

/// An [IdGenerator] that produces random RFC 4122 version 4 UUIDs.
///
/// This matches the default id generation of the other first-party
/// implementations (e.g. Java's `UUID.randomUUID()` and Ruby's
/// `Cucumber::Messages::Helpers::IdGenerator::UUID`), which both produce random
/// (version 4) UUIDs.
class UUID implements IdGenerator {
  static final Random _random = Random.secure();

  @override
  String newId() {
    // Generate 16 random bytes and set the version (4) and variant (RFC 4122)
    // bits, per RFC 4122 section 4.4.
    final bytes = List<int>.generate(16, (_) => _random.nextInt(256));
    bytes[6] = (bytes[6] & 0x0f) | 0x40; // version 4
    bytes[8] = (bytes[8] & 0x3f) | 0x80; // variant 10xx

    final hex = bytes.map((b) => b.toRadixString(16).padLeft(2, '0')).toList();
    return '${hex.getRange(0, 4).join()}-'
        '${hex.getRange(4, 6).join()}-'
        '${hex.getRange(6, 8).join()}-'
        '${hex.getRange(8, 10).join()}-'
        '${hex.getRange(10, 16).join()}';
  }
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
