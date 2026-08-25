import 'package:cucumber_gherkin/src/language/string_token_scanner.dart';
import 'package:test/test.dart';

void main() {
  test('scans LF, CRLF, final newlines, and repeated EOF reads', () {
    final scanner = StringTokenScanner('one\r\ntwo\n');

    expect(scanner.read().line!.getLineText(), 'one');
    expect(scanner.read().line!.getLineText(), 'two');
    expect(scanner.read().location.line, 3);
    expect(scanner.read().location.line, 4);
  });
}
