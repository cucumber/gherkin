import 'package:cucumber_gherkin/src/gherkin/id_generator.dart';
import 'package:test/test.dart';

final _uuidV4Pattern = RegExp(
  r'^[0-9a-f]{8}-[0-9a-f]{4}-4[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$',
);

void main() {
  group('Incrementing', () {
    test('produces sequential ids starting at 0', () {
      final generator = Incrementing();
      expect(generator.newId(), '0');
      expect(generator.newId(), '1');
      expect(generator.newId(), '2');
    });

    test('freshIncrementingGenerator restarts from 0 each time', () {
      IdGenerator.freshIncrementingGenerator.newId(); // advances a fresh one
      expect(IdGenerator.freshIncrementingGenerator.newId(), '0');
    });
  });

  group('UUID', () {
    test('produces RFC 4122 version 4 UUIDs', () {
      final generator = UUID();
      for (var i = 0; i < 100; i++) {
        final id = generator.newId();
        expect(
          id,
          matches(_uuidV4Pattern),
          reason: 'id "$id" is not a valid v4 UUID',
        );
      }
    });

    test('sets the version nibble to 4 and the variant to 10xx', () {
      final id = UUID().newId();
      // Format: xxxxxxxx-xxxx-Vxxx-Nxxx-xxxxxxxxxxxx
      expect(id[14], '4', reason: 'version nibble must be 4');
      expect('89ab', contains(id[19]), reason: 'variant nibble must be 8-b');
    });

    test('produces unique ids', () {
      final generator = UUID();
      final ids = {for (var i = 0; i < 1000; i++) generator.newId()};
      expect(ids, hasLength(1000));
    });
  });
}
