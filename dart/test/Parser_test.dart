import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:gherkin/parser.dart';
import 'package:gherkin/language.dart';
import 'package:gherkin/src/ast/messages_gherkin_document_builder.dart';
import 'package:test/test.dart';

void main() {
  test('Change default language', () {
    var languages = loadGherkinLanguagesFromJsonAsset();
    var dialectProvider = GherkinDialectProvider(languages, 'no');
    var matcher = TokenMatcher(dialectProvider);
    var idGenerator = IdGenerator.incrementingGenerator;

    var builder = MessagesGherkinDocumentBuilder(idGenerator);

    var tokenScanner = StringTokenScanner('Egenskap: i18n support\n');

    var parser = Parser<messages.GherkinDocument>(builder);

    var gherkinDocument = parser.parse(tokenScanner, matcher);

    expect('no', gherkinDocument.feature!.language);
  });
}
