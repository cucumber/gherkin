import 'package:cucumber_gherkin/cucumber_gherkin.dart';
import 'package:cucumber_gherkin/src/ast/messages_gherkin_document_builder.dart';
import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:cucumber_gherkin/src/language/gherkin_token_matcher.dart';
import 'package:cucumber_gherkin/src/language/string_token_scanner.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/pickles/messages_pickle_compiler.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  const languages = builtinDialects;
  final dialectProvider = GherkinDialectProvider(languages);
  final idGenerator = IdGenerator.incrementingGenerator;
  final builder = MessagesGherkinDocumentBuilder(idGenerator);
  final parser = Parser<messages.GherkinDocument>(builder);
  final matcher = GherkinTokenMatcher(dialectProvider);

  test('Is reusable', () {
    var tokenScanner = StringTokenScanner('Feature: 1');
    final d1 = parser.parse(tokenScanner, matcher);

    tokenScanner = StringTokenScanner('Feature: 2');
    final d2 = parser.parse(tokenScanner, matcher);

    expect(d1.feature!.name, '1');
    expect(d2.feature!.name, '2');
  });

  test('Parses rules', () {
    const data =
        'Feature: Some rules\n'
        '\n'
        '  Background:\n'
        '    Given fb\n'
        '\n'
        '  Rule: A\n'
        '    The rule A description\n'
        '\n'
        '    Background:\n'
        '      Given ab\n'
        '\n'
        '    Example: Example A\n'
        '      Given a\n'
        '\n'
        '  Rule: B\n'
        '    The rule B description\n'
        '\n'
        '    Example: Example B\n'
        '      Given b';

    final tokenScanner = StringTokenScanner(data);
    final doc = parser.parse(tokenScanner, matcher);

    final children = doc.feature!.children.toList();
    expect(children.length, 3);

    final pickleCompiler = MessagesPickleCompiler(idGenerator);
    final pickles = pickleCompiler.compile(doc, 'hello.feature');
    expect(2, pickles.length);

    expect(3, pickles.first.steps.length);

    expect(2, pickles.elementAt(1).steps.length);
  });

  test('Parses just comments', () {
    const data = '# Just a comment';
    final tokenScanner = StringTokenScanner(data);
    final doc = parser.parse(tokenScanner, matcher);
    final children = doc.comments;
    expect(children.length, 1);
  });

  test('Sets empty table cells', () {
    const data =
        'Feature:\n'
        '  Scenario:\n'
        '    Given a table\n'
        '      |a||b|';
    final tokenScanner = StringTokenScanner(data);
    final doc = parser.parse(tokenScanner, matcher);

    final row =
        doc.feature!.children.first.scenario!.steps.first.dataTable!.rows.first;
    expect('a', row.cells.first.value);
    expect('', row.cells.elementAt(1).value);
    expect('b', row.cells.elementAt(2).value);
  });
}
