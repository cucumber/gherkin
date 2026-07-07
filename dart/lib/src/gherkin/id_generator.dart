import 'dart:math';

/// Generates the ids assigned to emitted Cucumber messages.
abstract class IdGenerator {
  /// Creates an id generator.
  IdGenerator();

  /// Returns the next id.
  String newId();

  /// A shared [IncrementingIdGenerator] producing predictable, sequential ids.
  ///
  /// Single shared instance; its counter is never reset. For an independent
  /// counter (e.g. reproducible ids across separate parses), construct a fresh
  /// [IncrementingIdGenerator].
  static final IdGenerator incrementingGenerator = IncrementingIdGenerator();

  /// A shared [UuidIdGenerator] producing random UUIDs.
  static final IdGenerator uuidGenerator = UuidIdGenerator();
}

/// An [IdGenerator] that produces random RFC 4122 version 4 UUIDs.
///
/// Produces random RFC 4122 version 4 UUIDs.
class UuidIdGenerator implements IdGenerator {
  static final Random _random = Random.secure();

  /// Creates an id generator that produces random UUIDs.
  UuidIdGenerator();

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
class IncrementingIdGenerator implements IdGenerator {
  int _next = 0;

  /// Creates a sequential id generator starting at `0`.
  IncrementingIdGenerator();

  @override
  String newId() => (_next++).toString();
}
