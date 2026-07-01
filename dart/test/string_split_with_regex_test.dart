import 'package:cucumber_gherkin/src/extensions/strings.dart';
import 'package:test/test.dart';

void main() {
  const str = 'a bc def ghij klmno';
  final regexp = RegExp(r'\s');

  test('Split string using RegExp with limit 2 and specific char', () {
    const str2 = '@this @is #acomment  ';
    final regexp2 = RegExp(r'\s#');
    final result = str2.splitWithLimit(regexp2, limit: 2);
    expect(result[0], '@this @is');
  });

  test('Split string using RegExp with limit 0', () {
    final result = str.splitWithLimit(regexp);
    expect(result, ['a', 'bc', 'def', 'ghij', 'klmno']);
  });

  test('Split string using RegExp with limit 1', () {
    final result = str.splitWithLimit(regexp, limit: 1);
    expect(result, ['a bc def ghij klmno']);
  });

  test('Split string using RegExp with limit 2', () {
    final result = str.splitWithLimit(regexp, limit: 2);
    expect(result, ['a', 'bc def ghij klmno']);
  });

  test('Split string using RegExp with limit 3', () {
    final result = str.splitWithLimit(regexp, limit: 3);
    expect(result, ['a', 'bc', 'def ghij klmno']);
  });

  test('Split string using RegExp with limit 4', () {
    final result = str.splitWithLimit(regexp, limit: 4);
    expect(result, ['a', 'bc', 'def', 'ghij klmno']);
  });

  test('Split string using RegExp with limit 5', () {
    final result = str.splitWithLimit(regexp, limit: 5);
    expect(result, ['a', 'bc', 'def', 'ghij', 'klmno']);
  });

  test('Split string using RegExp with limit 6', () {
    final result = str.splitWithLimit(regexp, limit: 6);
    expect(result, ['a', 'bc', 'def', 'ghij', 'klmno']);
  });

  test('Split string using RegExp with limit 3 but without the pattern', () {
    final regexp2 = RegExp('[@]');
    final result = str.splitWithLimit(regexp2, limit: 3);
    expect(result, [str]);
  });

  test('Split string using RegExp with limit negative', () {
    expect(
      () => str.splitWithLimit(regexp, limit: -1),
      throwsA(const TypeMatcher<UnimplementedError>()),
    );
  });
}
