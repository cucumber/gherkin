import 'package:cucumber_gherkin/src/compile_pickles.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

void main() {
  test('does not assign a pickle step type to conjunctions', () {
    expect(pickleStepType(messages.StepKeywordType.conjunction), isNull);
  });
}
