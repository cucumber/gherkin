import 'dart:math';

import 'package:cucumber_gherkin/src/compile_pickles.dart';
import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/gherkin_document_builder.dart';
import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:cucumber_gherkin/src/language/gherkin_token_matcher.dart';
import 'package:cucumber_gherkin/src/language/string_token_scanner.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// Controls which envelopes [generateMessages] emits and how IDs are assigned.
final class GherkinOptions {
  /// Creates options with Cucumber-compatible defaults (`source`,
  /// `gherkinDocument`, and `pickle` envelopes included; English dialect;
  /// random UUIDs).
  const GherkinOptions({
    this.includeSource = true,
    this.includeGherkinDocument = true,
    this.includePickles = true,
    this.defaultDialect = 'en',
    this.idGenerator,
  });

  /// Whether to emit a `source` envelope for the input.
  final bool includeSource;

  /// Whether to emit a `gherkinDocument` envelope for a successful parse.
  final bool includeGherkinDocument;

  /// Whether to emit `pickle` envelopes compiled from the document.
  final bool includePickles;

  /// Language tag used when the source does not declare `# language: …`.
  final String defaultDialect;

  /// Supplies unique IDs for Gherkin document nodes and pickles.
  ///
  /// When null, each ID is a random UUID v4.
  final String Function()? idGenerator;
}

/// Parses Gherkin [data] identified by [uri] into Cucumber message envelopes.
///
/// Malformed Gherkin is reported as `parseError` envelopes rather than thrown
/// exceptions.
List<messages.Envelope> generateMessages(
  String data,
  String uri, [
  GherkinOptions options = const GherkinOptions(),
]) {
  final idGenerator = options.idGenerator ?? _newUuidV4;
  final result = <messages.Envelope>[];

  final source = messages.Source(
    uri: uri,
    data: data,
    mediaType: messages.SourceMediaType.textXCucumberGherkinPlain,
  );

  if (options.includeSource) {
    result.add(messages.Envelope(source: source));
  }

  if (!options.includeGherkinDocument && !options.includePickles) {
    return result;
  }

  final builder = GherkinDocumentBuilder(idGenerator);
  final parser = Parser<messages.GherkinDocument>(builder);
  final tokenScanner = StringTokenScanner(source.data);

  final messages.GherkinDocument gherkinDocument;
  try {
    gherkinDocument = parser.parse(
      tokenScanner,
      GherkinTokenMatcher(builtinDialects, options.defaultDialect),
    );
  } on CompositeParserException catch (e) {
    result.addAll(
      e.errors.map((error) => _parseErrorEnvelope(error, source.uri)),
    );
    return result;
  } on ParserException catch (e) {
    result.add(_parseErrorEnvelope(e, source.uri));
    return result;
  }

  final gherkinDocumentWithUri = messages.GherkinDocument(
    uri: source.uri,
    feature: gherkinDocument.feature,
    comments: gherkinDocument.comments,
  );

  if (options.includeGherkinDocument) {
    result.add(messages.Envelope(gherkinDocument: gherkinDocumentWithUri));
  }

  if (options.includePickles) {
    for (final pickle in compilePickles(
      gherkinDocumentWithUri,
      source.uri,
      idGenerator,
    )) {
      result.add(messages.Envelope(pickle: pickle));
    }
  }

  return result;
}

messages.Envelope _parseErrorEnvelope(ParserException error, String uri) {
  // Error messages already include a `(line:column)` prefix; pass through
  // verbatim and attach a structured location when available.
  final loc = error.location;
  return messages.Envelope(
    parseError: messages.ParseError(
      source: messages.SourceReference(
        uri: uri,
        location:
            loc.isEmpty || loc.line == 0
                ? null
                : messages.Location(
                  line: loc.line,
                  column: loc.column == 0 ? null : loc.column,
                ),
      ),
      message: error.message,
    ),
  );
}

// RFC 4122 UUID v4.
String _newUuidV4() {
  final random = Random.secure();
  final bytes = List<int>.generate(16, (_) => random.nextInt(256));
  bytes[6] = (bytes[6] & 0x0f) | 0x40;
  bytes[8] = (bytes[8] & 0x3f) | 0x80;
  final hex = bytes.map((byte) => byte.toRadixString(16).padLeft(2, '0'));
  return '${hex.take(4).join()}-${hex.skip(4).take(2).join()}-'
      '${hex.skip(6).take(2).join()}-${hex.skip(8).take(2).join()}-'
      '${hex.skip(10).join()}';
}
