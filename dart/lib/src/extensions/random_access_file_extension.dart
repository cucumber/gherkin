import 'dart:convert';
import 'dart:io';

/// Synchronous, line-oriented helpers used by the file-based token scanner.
extension RandomAccessFileExtension on RandomAccessFile {
  /// The line-feed byte (`\n`).
  static const lf = 10;

  /// The carriage-return byte (`\r`).
  static const cr = 13;

  /// The sentinel byte returned at end of file.
  static const eof = -1;

  /// Synchronously reads a single line from the file. If end-of-file
  /// has been reached then `null` string is returned.
  /// If not specified, [encoding] uses [utf8].
  ///
  /// A line is terminated by `\n` or `\r\n`; the terminator is not included in
  /// the returned string. A lone `\r` that is *not* immediately followed by
  /// `\n` is treated as ordinary content and preserved, matching the reference
  /// Gherkin implementations, which split lines on `\r?\n` (see
  /// `TokenScanner` in the JavaScript implementation). This keeps the file and
  /// string scanners consistent.
  ///
  /// Throws a [FileSystemException] if the operation fails.
  String? readLineSync({Encoding encoding = utf8}) {
    final line = <int>[];
    int chr;
    if ((chr = readByteSync()) == eof) {
      return null;
    }
    do {
      if (chr == lf) {
        break;
      }
      if (chr == cr && peekByteSync() == lf) {
        // Consume the `\n` of a `\r\n` terminator and end the line.
        readByteSync();
        break;
      }
      line.add(chr);
    } while ((chr = readByteSync()) != eof);
    return encoding.decode(line);
  }

  /// Synchronously peeks a single byte from the file without moving the
  /// position pointer.
  ///
  /// Throws a [FileSystemException] if the operation fails.
  int peekByteSync() {
    final position = positionSync();
    final char = readByteSync();
    setPositionSync(position);
    return char;
  }

  /// Synchronously read a single byte from the file skipping the code bytes
  /// specified in [charsToAvoid].
  ///
  /// Throws a [FileSystemException] if the operation fails.
  int readByteSyncSkipping(Set<int> charsToAvoid) {
    int lastReadChar;
    while (charsToAvoid.contains(lastReadChar = readByteSync())) {}
    return lastReadChar;
  }
}
