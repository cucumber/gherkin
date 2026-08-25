import 'package:cucumber_gherkin/src/language/string_token_scanner.dart';
import 'package:test/test.dart';

void main() {
  test('represents EOF without a line', () {
    final token = StringTokenScanner('').read();

    expect(token.isEof, isTrue);
    expect(token.line, isNull);
    expect(token.tokenValue, 'EOF');
  });
}
