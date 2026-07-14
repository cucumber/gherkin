import 'dart:math';

import 'package:cucumber_gherkin/src/compile_pickles.dart';
import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/gherkin_document_builder.dart';
import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:cucumber_gherkin/src/language/gherkin_token_matcher.dart';
import 'package:cucumber_gherkin/src/language/string_token_scanner.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// Controls envelopes emitted by [generateMessages] and ID generation.
final class GherkinOptions {
  /// Creates options with Cucumber-compatible defaults.
  const GherkinOptions({
    this.includeSource = true,
    this.includeGherkinDocument = true,
    this.includePickles = true,
    this.defaultDialect = 'en',
    this.idGenerator,
  });

  /// Whether to emit a source envelope.
  final bool includeSource;

  /// Whether to emit a Gherkin document envelope after a successful parse.
  final bool includeGherkinDocument;

  /// Whether to emit pickle envelopes.
  final bool includePickles;

  /// Language used when the source has no language header.
  final String defaultDialect;

  /// Supplies IDs for AST elements, pickles, and pickle steps.
  final String Function()? idGenerator;
}

/// Parses Gherkin [data] at [uri] into Cucumber message envelopes.
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
