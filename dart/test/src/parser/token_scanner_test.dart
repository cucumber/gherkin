import 'package:cucumber_gherkin/src/parser/token_scanner.dart';
import 'package:test/test.dart';

void main() {
  test('represents empty input as EOF on the first line', () {
    final token = TokenScanner('').read();

    expect(token.isEof, isTrue);
    expect(token.line, isNull);
    expect(token.tokenValue, 'EOF');
    expect(token.location.line, 1);
  });

  test('reads the final line without a trailing newline', () {
    final scanner = TokenScanner('  first\n  last  ')..read();
    final last = scanner.read();
    final eof = scanner.read();

    expect(last.line!.getLineText(), '  last  ');
    expect(last.location.line, 2);
    expect(eof.isEof, isTrue);
    expect(eof.location.line, 3);
  });

  test(
    'splits LF and CRLF, retaining blank lines but not trailing newline',
    () {
      final scanner = TokenScanner(' first\r\n\nlast\n');
      final first = scanner.read();
      final blank = scanner.read();
      final last = scanner.read();
      final eof = scanner.read();

      expect(
        [first.tokenValue, blank.tokenValue, last.tokenValue],
        [
          'first',
          '',
          'last',
        ],
      );
      expect(
        [first.location.line, blank.location.line, last.location.line],
        [
          1,
          2,
          3,
        ],
      );
      expect(eof.isEof, isTrue);
      expect(eof.location.line, 4);
    },
  );
}
