import 'dart:io';

import 'package:test/test.dart';

import '../../../tool/random_access_file_extension.dart';

void main() {
  final currDir = Directory.current.path.replaceAll(r'\', '/');
  const assetDir = 'test/assets';

  test('Read lines with only CR keeps lone CR as content', () async {
    // A lone `\r` is not a line separator (only `\n` and `\r\n` are), matching
    // the reference implementations' `\r?\n` splitting. The whole file is one
    // line and the `\r` bytes are preserved verbatim.
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
    const expectedText =
        'Testing\rbreak\rlines\rwith\rcharacter\rCR\r(\rCarriage\rReturn\r)\r';
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
    // Only the `\r` immediately preceding `\n` forms the terminator; any extra
    // leading `\r`s are content and are preserved. The first line here is
    // "Testing" followed by five `\r` and a `\n`, so four `\r`s remain.
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
        'Testing\r\r\r\r'
        'breaklineswithmultiplesCRbeforeLF(CarriageReturnandLineFeed)';
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
