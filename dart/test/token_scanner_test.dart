import 'package:cucumber_gherkin/src/parser/token_scanner.dart';
import 'package:test/test.dart';

void main() {
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
