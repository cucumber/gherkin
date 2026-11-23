import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:test/test.dart';

void main() {
  test('formats an exception without a source location', () {
    final exception = ParserException.create('Invalid input');

    expect(exception.location.line, -1);
    expect(exception.location.column, 0);
    expect(exception.message, '(-1,0): Invalid input');
    expect(exception.toString(), exception.message);
  });
}
