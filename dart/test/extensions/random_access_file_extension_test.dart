import 'dart:io';

import 'package:cucumber_gherkin/src/extensions/random_access_file_extension.dart';
import 'package:test/test.dart';

void main() {
  final currDir = Directory.current.path.replaceAll(r'\', '/');
  const assetDir = 'test/assets';

  test('Read lines with only CR', () async {
    final filepath = '$currDir/$assetDir/text-with-only-cr.txt';
    final textFile = File(filepath).openSync();
    final buffer = StringBuffer();
    String? line;
    var lineCount = 0;

    while ((line = textFile.readLineSync()) != null) {
      buffer.write(line);
      lineCount++;
    }

    expect(lineCount, 1);

    final text = buffer.toString();
    const expectedText = 'TestingbreaklineswithcharacterCR(CarriageReturn)';
    expect(text, expectedText);
  });

  test('Read lines with only LF', () async {
    final filepath = '$currDir/$assetDir/text-with-only-lf.txt';
    final textFile = File(filepath).openSync();
    final buffer = StringBuffer();
    String? line;
    var lineCount = 0;

    while ((line = textFile.readLineSync()) != null) {
      buffer.write(line);
      lineCount++;
    }

    expect(lineCount, 10);

    final text = buffer.toString();
    const expectedText = 'TestingbreaklineswithcharacterLF(LineFeed)';
    expect(text, expectedText);
  });

  test('Read lines with CR and LF', () async {
    final filepath = '$currDir/$assetDir/text-with-cr-and-lf.txt';
    final textFile = File(filepath).openSync();
    final buffer = StringBuffer();
    String? line;
    var lineCount = 0;

    while ((line = textFile.readLineSync()) != null) {
      buffer.write(line);
      lineCount++;
    }

    expect(lineCount, 15);

    final text = buffer.toString();
    const expectedText =
        'TestingbreaklineswithsequenceCRandLF(CarriageReturnandLineFeed)';
    expect(text, expectedText);
  });

  test('Read lines with multiples CR before LF', () async {
    final filepath = '$currDir/$assetDir/text-with-multiples-cr-before-lf.txt';
    final textFile = File(filepath).openSync();
    final buffer = StringBuffer();
    String? line;
    var lineCount = 0;

    while ((line = textFile.readLineSync()) != null) {
      buffer.write(line);
      lineCount++;
    }

    expect(lineCount, 15);

    final text = buffer.toString();
    const expectedText =
        'TestingbreaklineswithmultiplesCRbeforeLF(CarriageReturnandLineFeed)';
    expect(text, expectedText);
  });

  test('Read file without CR/LF in the last line', () async {
    final filepath = '$currDir/$assetDir/text-without-cr-lf-last-line.txt';
    final textFile = File(filepath).openSync();
    final buffer = StringBuffer();
    String? line;
    var lineCount = 0;

    while ((line = textFile.readLineSync()) != null) {
      buffer.write(line);
      lineCount++;
    }

    expect(lineCount, 8);

    final text = buffer.toString();
    const expectedText = 'TextwithoutCRorinthelastline';
    expect(text, expectedText);
  });
}
