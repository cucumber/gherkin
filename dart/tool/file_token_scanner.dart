import 'dart:io';

import 'package:cucumber_gherkin/src/language/gherkin_line.dart';
import 'package:cucumber_gherkin/src/language/location.dart';
import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/token_scanner.dart';

import 'random_access_file_extension.dart';

/// A [TokenScanner] that reads a Gherkin document from a file (typically a
/// `.feature` file), producing one token per line.
///
/// The tokens are passed to the parser, which outputs an abstract syntax tree
/// (AST).
///
/// If the scanner sees a `#` language header, the matcher reconfigures itself
/// to look for the Gherkin keywords of the associated language. Those keywords
/// are defined in `gherkin-languages.json`.
class FileTokenScanner implements TokenScanner {
  /// Creates a scanner that reads the file at [filepath].
  FileTokenScanner.fromPath(String filepath)
    : _access = File(filepath).openSync();

  /// Creates a scanner that reads the given [file].
  FileTokenScanner.fromFile(File file) : _access = file.openSync();

  /// The number of lines read so far (the line of the most recent token).
  int lineNumber = 0;

  final RandomAccessFile _access;

  @override
  Token read() {
    final line = _access.readLineSync();
    final location = Location(++lineNumber, 0);
    return line == null
        ? Token(GherkinLine.eof(), location)
        : Token(GherkinLine(line, lineNumber), location);
  }
}
