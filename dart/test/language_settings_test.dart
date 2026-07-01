import 'package:cucumber_gherkin/src/language/gherkin_languages_loader.dart';
import 'package:test/test.dart';

void main() {
  test('Load language settings from json assets', () {
    final settings = loadGherkinLanguagesFromJsonAsset();
    expect(settings, isNotEmpty);
    expect(settings['en'], isNotNull);
    expect(settings['en']?.name.toLowerCase(), 'english');
    expect(settings['en']?.native.toLowerCase(), 'english');
    expect(settings['en']?.background[0].toLowerCase(), 'background');
  });
}
