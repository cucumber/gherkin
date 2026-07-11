import 'dart:math';

import 'package:cucumber_gherkin/src/ast/messages_gherkin_document_builder.dart';
import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:cucumber_gherkin/src/language/gherkin_dialect_provider.dart';
import 'package:cucumber_gherkin/src/language/gherkin_token_matcher.dart';
import 'package:cucumber_gherkin/src/language/string_token_scanner.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/pickles/messages_pickle_compiler.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// Parses Gherkin documents into Cucumber [messages.Envelope]s.
///
/// Streams are lazy across sources but eager within a source. Malformed Gherkin
/// is reported as `parseError` envelopes rather than thrown exceptions.
class GherkinParser {
  /// Creates a parser.
  GherkinParser({
    bool includeSource = true,
    bool includeGherkinDocument = true,
    bool includePickles = true,
    String defaultDialect = 'en',
    String Function()? idGenerator,
  }) : _includeSource = includeSource,
       _includeGherkinDocument = includeGherkinDocument,
       _includePickles = includePickles,
       _idGenerator = idGenerator ?? _newUuid {
    _dialectProvider = GherkinDialectProvider(builtinDialects, defaultDialect);
  }

  final bool _includeSource;
  final bool _includeGherkinDocument;
  final bool _includePickles;

  /// The function used to assign ids to emitted messages.
  final String Function() _idGenerator;

  late final GherkinDialectProvider _dialectProvider;

  /// Parses in-memory Gherkin [data] identified by [uri].
  Stream<messages.Envelope> parseString(String data, String uri) async* {
    final envelope = messages.Envelope(
      source: messages.Source(
        uri: uri,
        data: data,
        mediaType: messages.SourceMediaType.textXCucumberGherkinPlain,
      ),
    );
    if (_includeSource) {
      yield envelope;
    }
    yield* Stream.fromIterable(_parseSource(envelope.source!));
  }

  Iterable<messages.Envelope> _parseSource(messages.Source source) sync* {
    if (!_includeGherkinDocument && !_includePickles) {
      return;
    }

    final builder = MessagesGherkinDocumentBuilder(_idGenerator);
    final parser = Parser<messages.GherkinDocument>(builder)
      ..stopAtFirstError = false;
    final tokenScanner = StringTokenScanner(source.data);

    final messages.GherkinDocument gherkinDocument;
    try {
      gherkinDocument = parser.parse(
        tokenScanner,
        GherkinTokenMatcher(_dialectProvider),
      );
    } on CompositeParserException catch (e) {
      yield* e.errors.map((error) => _parseErrorEnvelope(error, source.uri));
      return;
    } on ParserException catch (e) {
      yield _parseErrorEnvelope(e, source.uri);
      return;
    }

    final gherkinDocumentWithUri = messages.GherkinDocument(
      uri: source.uri,
      feature: gherkinDocument.feature,
      comments: gherkinDocument.comments,
    );

    if (_includeGherkinDocument) {
      yield messages.Envelope(gherkinDocument: gherkinDocumentWithUri);
    }
    if (_includePickles) {
      final pickleCompiler = MessagesPickleCompiler(_idGenerator);
      for (final pickle in pickleCompiler.compile(
        gherkinDocumentWithUri,
        source.uri,
      )) {
        yield messages.Envelope(pickle: pickle);
      }
    }
  }

  messages.Envelope _parseErrorEnvelope(ParserException error, String uri) {
    // The error message already carries its `(line:column): ` (or `(-1,0): `)
    // position prefix; emit it verbatim and add the structured source location
    // alongside it.
    if (error.location.isEmpty) {
      return messages.Envelope(
        parseError: messages.ParseError(
          source: messages.SourceReference(uri: uri),
          message: error.message,
        ),
      );
    }

    final line = error.location.line;
    final column = error.location.column;
    return messages.Envelope(
      parseError: messages.ParseError(
        source: messages.SourceReference(
          uri: uri,
          location:
              line == 0
                  ? null
                  : messages.Location(
                    line: line,
                    column: column == 0 ? null : column,
                  ),
        ),
        message: error.message,
      ),
    );
  }
}

String _newUuid() {
  final random = Random.secure();
  final bytes = List<int>.generate(16, (_) => random.nextInt(256));
  bytes[6] = (bytes[6] & 0x0f) | 0x40;
  bytes[8] = (bytes[8] & 0x3f) | 0x80;
  final hex = bytes.map((byte) => byte.toRadixString(16).padLeft(2, '0'));
  return '${hex.take(4).join()}-${hex.skip(4).take(2).join()}-'
      '${hex.skip(6).take(2).join()}-${hex.skip(8).take(2).join()}-'
      '${hex.skip(10).join()}';
}
