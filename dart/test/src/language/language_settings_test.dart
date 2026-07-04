import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:test/test.dart';

void main() {
  test('Load language settings from json assets', () {
    const settings = builtinDialects;
    expect(settings, isNotEmpty);
    expect(settings['en'], isNotNull);
    expect(settings['en']?.name.toLowerCase(), 'english');
    expect(settings['en']?.native.toLowerCase(), 'english');
    expect(settings['en']?.background[0].toLowerCase(), 'background');
  });
}
