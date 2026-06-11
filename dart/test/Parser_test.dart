import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:gherkin/language.dart';
import 'package:gherkin/parser.dart';
import 'package:gherkin/src/ast/messages_gherkin_document_builder.dart';
import 'package:test/test.dart';

void main() {
  test('Change default language', () {
    final languages = loadGherkinLanguagesFromJsonAsset();
    final dialectProvider = GherkinDialectProvider(languages, 'no');
    final matcher = TokenMatcher(dialectProvider);
    final idGenerator = IdGenerator.incrementingGenerator;

    final builder = MessagesGherkinDocumentBuilder(idGenerator);

    final tokenScanner = StringTokenScanner('Egenskap: i18n support\n');

    final parser = Parser<messages.GherkinDocument>(builder);

    final gherkinDocument = parser.parse(tokenScanner, matcher);

    expect('no', gherkinDocument.feature!.language);
  });
}
