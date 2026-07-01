import 'package:gherkin/src/extensions/strings.dart';
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
      throwsA(const TypeMatcher<UnimplementedError>()),
    );
  });
}
