import 'package:cucumber_gherkin/src/extensions/int_extensions.dart';
import 'package:test/test.dart';

void main() {
  group('Int.min sentinel', () {
    test('is negative so it cannot collide with real positions', () {
      // Line numbers, columns and indents are always non-negative, so the
      // "unset" sentinel must be negative to be unambiguous.
      expect(Int.min, lessThan(0));
    });

    test('is portable across VM and web/JS targets', () {
      // A previous implementation used `1 << 63`, which does not produce the
      // 64-bit minimum integer when compiled to JavaScript. Assert on the
      // exact, platform-independent value instead.
      expect(Int.min, -1);
      // Guard against a regression to the non-portable bit-shift value: on the
      // VM `1 << 63` is the most-negative int, on the web it is not, so it must
      // never be reintroduced as the sentinel.
      expect(Int.min, isNot(equals(1 << 63)));
    });
  });

  group('IntExtensions.isMin / isNotMin', () {
    test('isMin is true only for the sentinel', () {
      expect(Int.min.isMin, isTrue);
      expect(0.isMin, isFalse);
      expect(1.isMin, isFalse);
      expect(42.isMin, isFalse);
      expect((-2).isMin, isFalse);
    });

    test('isNotMin is the inverse of isMin', () {
      expect(Int.min.isNotMin, isFalse);
      expect(0.isNotMin, isTrue);
      expect(1.isNotMin, isTrue);
      expect(42.isNotMin, isTrue);
      expect((-2).isNotMin, isTrue);
    });

    test('all realistic positions are treated as set (not min)', () {
      for (final position in [0, 1, 2, 10, 100, 1000, 1 << 30]) {
        expect(position.isMin, isFalse, reason: 'position $position');
        expect(position.isNotMin, isTrue, reason: 'position $position');
      }
    });
  });
}
