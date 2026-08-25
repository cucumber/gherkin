import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/parser/gherkin_line.dart';
import 'package:cucumber_gherkin/src/parser/token.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  test('formats parser exceptions using token and explicit locations', () {
    final token = Token(
      GherkinLine('  bad', 7),
      const messages.Location(line: 7),
    );
    final located = AstBuilderException(
      'bad table',
      const messages.Location(line: 2, column: 3),
    );
    final unexpected = UnexpectedTokenException(token, ['ScenarioLine']);
    final eof = UnexpectedEofException(
      Token.eof(const messages.Location(line: 9)),
      ['EOF'],
    );
    final composite = CompositeParserException([located, unexpected]);

    expect(located.message, '(2:3): bad table');
    expect(located.toString(), '(2:3): bad table');
    expect(unexpected.message, contains('(7:3): expected: ScenarioLine'));
    expect(eof.message, '(9:0): unexpected end of file, expected: EOF');
    expect(composite.message, contains('Parser errors:\n(2:3): bad table'));
    expect(
      NoSuchLanguageException('xx').message,
      '(-1,0): Language not supported: xx',
    );
  });
}
