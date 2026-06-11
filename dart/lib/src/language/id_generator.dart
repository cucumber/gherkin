import 'package:uuid/uuid.dart';

abstract class IdGenerator {
  String newId();

  static final IdGenerator incrementingGenerator = Incrementing();

  /// Returns a **new** [Incrementing] instance each time; safe for per-test use.
  static IdGenerator get freshIncrementingGenerator => Incrementing();

  static final IdGenerator uuidGenerator = UUID();
}

class UUID implements IdGenerator {
  final Uuid _uuid = Uuid();

  @override
  String newId() => _uuid.v1();
}

class Incrementing implements IdGenerator {
  int _next = -1;

  @override
  String newId() {
    _next++;
    return _next.toString();
  }
}
