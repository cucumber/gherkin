import 'dart:io';

import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/gherkin/gherkin_parser.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// File-system entry points for [GherkinParser].
///
/// These live in a separate library because they depend on `dart:io`, which is
/// unavailable on the web. Importing `package:cucumber_gherkin/cucumber_gherkin.dart`
/// keeps the parser platform-agnostic (string/envelope entry points only);
/// import `package:cucumber_gherkin/cucumber_gherkin_io.dart` to additionally
/// read Gherkin from files.
extension GherkinParserIo on GherkinParser {
  /// Parses the file at [path] and emits the resulting envelopes.
  ///
  /// The file is read asynchronously (without blocking the isolate) when the
  /// stream is first listened to.
  ///
  /// I/O failures (e.g. the file does not exist) are surfaced as a
  /// [GherkinException] error event on the stream rather than emitted as a
  /// `parseError` envelope: they are not a property of the Gherkin source. This
  /// matches the flagship implementations, where the path-based entry point
  /// surfaces I/O errors to the caller (e.g. Java's `GherkinParser.parse(Path)`
  /// declares `throws IOException`). Malformed Gherkin, by contrast, is always
  /// reported as a `parseError` envelope.
  Stream<messages.Envelope> parsePath(String path) async* {
    final String data;
    try {
      // Read the file verbatim. The `source` envelope's `data` must preserve
      // the original bytes (including CRLF), matching the other first-party
      // implementations (e.g. Go sets `Data: string(in)`); the line scanner
      // tolerates CRLF when classifying tokens.
      data = await File(path).readAsString();
    } on IOException catch (e) {
      throw GherkinException(e.toString(), e);
    }
    yield* parseEnvelope(GherkinParser.makeSourceEnvelope(data, path));
  }

  /// Parses each path in [paths] and emits the resulting envelopes.
  ///
  /// Paths are processed lazily and in order: a path is not read or parsed
  /// until the preceding path's envelopes have been consumed.
  Stream<messages.Envelope> parsePaths(Iterable<String> paths) {
    return Stream.fromIterable(paths).asyncExpand(parsePath);
  }
}
