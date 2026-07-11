import 'package:cucumber_gherkin/cucumber_gherkin.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  var nextId = 0;
  String nextIdGenerator() => (nextId++).toString();

  Future<List<messages.Envelope>> parse(String data) {
    return GherkinParser(
      includeSource: false,
      includePickles: false,
      idGenerator: nextIdGenerator,
    ).parseString(data, 'bad.feature').toList();
  }

  test('reports malformed input as a parseError envelope', () async {
    final envelopes = await parse('not gherkin');

    expect(envelopes, hasLength(1));
    final error = envelopes.single.parseError!;
    expect(error.message, startsWith('(1:1): '));
    expect(error.source.location!.line, 1);
  });

  test('reports an unsupported dialect as a parseError envelope', () async {
    final envelopes = await parse('#language:no-such\nFeature: x\n');

    final error = envelopes.single.parseError!;
    expect(error.message, contains('Language not supported: no-such'));
    expect(error.source.location!.line, 1);
  });
}
