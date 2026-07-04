import 'package:cucumber_gherkin/src/extensions/strings.dart';
import 'package:test/test.dart';

void main() {
  const str = 'a bc def ghij klmno';
  var pattern = ' ';

  test('Split with limit 0', () {
    final result = str.splitWithLimit(pattern);
    expect(result, ['a', 'bc', 'def', 'ghij', 'klmno']);
  });

  test('Split with limit 1', () {
    final result = str.splitWithLimit(pattern, limit: 1);
    expect(result, ['a bc def ghij klmno']);
  });

  test('Split with limit 2', () {
    final result = str.splitWithLimit(pattern, limit: 2);
    expect(result, ['a', 'bc def ghij klmno']);
  });

  test('Split with limit 3', () {
    final result = str.splitWithLimit(pattern, limit: 3);
    expect(result, ['a', 'bc', 'def ghij klmno']);
  });

  test('Split with limit 4', () {
    final result = str.splitWithLimit(pattern, limit: 4);
    expect(result, ['a', 'bc', 'def', 'ghij klmno']);
  });

  test('Split with limit 5', () {
    final result = str.splitWithLimit(pattern, limit: 5);
    expect(result, ['a', 'bc', 'def', 'ghij', 'klmno']);
  });

  test('Split with limit 6', () {
    final result = str.splitWithLimit(pattern, limit: 6);
    expect(result, ['a', 'bc', 'def', 'ghij', 'klmno']);
  });

  test('Split with limit 3 but without the pattern', () {
    pattern = '@';
    final result = str.splitWithLimit(pattern, limit: 3);
    expect(result, [str]);
  });

  test('Split with limit negative', () {
    expect(
      () => str.splitWithLimit(pattern, limit: -1),
      throwsA(const TypeMatcher<ArgumentError>()),
    );
  });

  test('Repeated substring is split at the correct offset', () {
    // The first field ("a") also appears inside a later field. The remainder
    // must be the text after the second separator, not after the first "a".
    const repeated = 'a b a c';
    expect(repeated.splitWithLimit(' ', limit: 2), ['a', 'b a c']);
    expect(repeated.splitWithLimit(' ', limit: 3), ['a', 'b', 'a c']);
  });

  test('Multi-character separator preserves the full remainder', () {
    // A multi-character separator must not drop a character from the remainder.
    const csv = 'a::b::c::d';
    expect(csv.splitWithLimit('::', limit: 2), ['a', 'b::c::d']);
    expect(csv.splitWithLimit('::', limit: 3), ['a', 'b', 'c::d']);
  });

  test('Remainder retains further separators', () {
    expect(str.splitWithLimit(' ', limit: 2), ['a', 'bc def ghij klmno']);
  });

  test('Leading separator yields a leading empty field', () {
    expect(' a b'.splitWithLimit(' ', limit: 2), ['', 'a b']);
  });
}
