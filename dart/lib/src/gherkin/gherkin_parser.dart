import 'package:cucumber_gherkin/src/ast/messages_gherkin_document_builder.dart';
import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/gherkin/id_generator.dart';
import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:cucumber_gherkin/src/language/gherkin_dialect_provider.dart';
import 'package:cucumber_gherkin/src/language/gherkin_token_matcher.dart';
import 'package:cucumber_gherkin/src/language/string_token_scanner.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/parser/token_matcher.dart';
import 'package:cucumber_gherkin/src/pickles/messages_pickle_compiler.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// Parses Gherkin documents into Cucumber [messages.Envelope]s.
///
/// Streams are lazy across sources but eager within a source. Malformed Gherkin
/// is reported as `parseError` envelopes rather than thrown exceptions.
class GherkinParser {
  /// Creates a parser.
  GherkinParser({
    this.includeSource = defaultIncludeSource,
    this.includeGherkinDocument = defaultIncludeGherkinDocument,
    this.includePickles = defaultIncludePickles,
    this.defaultDialect = defaultDialectValue,
    IdGenerator? idGenerator,
  }) : idGenerator = idGenerator ?? IdGenerator.uuidGenerator {
    _dialectProvider = GherkinDialectProvider(builtinDialects, defaultDialect);
  }

  /// The default for [includeSource]: `source` envelopes are emitted.
  static const bool defaultIncludeSource = true;

  /// The default for [includeGherkinDocument]: `gherkinDocument` envelopes are
  /// emitted.
  static const bool defaultIncludeGherkinDocument = true;

  /// The default for [includePickles]: `pickle` envelopes are emitted.
  static const bool defaultIncludePickles = true;

  /// The default for [defaultDialect]: the `en` dialect.
  static const String defaultDialectValue = 'en';

  /// Whether `source` envelopes are emitted.
  final bool includeSource;

  /// Whether `gherkinDocument` envelopes are emitted.
  final bool includeGherkinDocument;

  /// Whether `pickle` envelopes are emitted.
  final bool includePickles;

  /// The dialect used when a feature has no `# language:` header.
  final String defaultDialect;

  /// The [IdGenerator] used to assign ids to emitted messages.
  final IdGenerator idGenerator;

  late final GherkinDialectProvider _dialectProvider;

  /// Parses in-memory Gherkin [data] identified by [uri].
  ///
  /// Throws an [ArgumentError] when [mediaType] is omitted and the [uri]
  /// extension is not recognized.
  Stream<messages.Envelope> parseString(
    String data,
    String uri, {
    messages.SourceMediaType? mediaType,
  }) {
    return parseEnvelope(makeSourceEnvelope(data, uri, mediaType: mediaType));
  }

  /// Parses a single source [envelope].
  Stream<messages.Envelope> parseEnvelope(messages.Envelope envelope) async* {
    if (includeSource) {
      yield envelope;
    }
    final source = envelope.source;
    if (source == null) {
      return;
    }
    yield* Stream.fromIterable(_parseSource(source));
  }

  Iterable<messages.Envelope> _parseSource(messages.Source source) sync* {
    if (!includeGherkinDocument && !includePickles) {
      return;
    }

    final builder = MessagesGherkinDocumentBuilder(idGenerator);
    final parser = Parser<messages.GherkinDocument>(builder)
      ..stopAtFirstError = false;
    final tokenScanner = StringTokenScanner(source.data);

    final messages.GherkinDocument gherkinDocument;
    try {
      final tokenMatcher = _tokenMatcher(source.mediaType);
      gherkinDocument = parser.parse(tokenScanner, tokenMatcher);
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

    if (includeGherkinDocument) {
      yield messages.Envelope(gherkinDocument: gherkinDocumentWithUri);
    }
    if (includePickles) {
      final pickleCompiler = MessagesPickleCompiler(idGenerator);
      for (final pickle in pickleCompiler.compile(
        gherkinDocumentWithUri,
        source.uri,
      )) {
        yield messages.Envelope(pickle: pickle);
      }
    }
  }

  /// Parses a stream of source [envelopes] and emits the resulting envelopes.
  ///
  /// Envelopes are processed lazily and in order: a source is not parsed until
  /// the preceding source's envelopes have been consumed.
  Stream<messages.Envelope> parseEnvelopes(
    Stream<messages.Envelope> envelopes,
  ) {
    return envelopes.asyncExpand(parseEnvelope);
  }

  TokenMatcher _tokenMatcher(messages.SourceMediaType mediaType) {
    switch (mediaType) {
      case messages.SourceMediaType.textXCucumberGherkinPlain:
        return GherkinTokenMatcher(_dialectProvider);
      case messages.SourceMediaType.textXCucumberGherkinMarkdown:
        throw UnsupportedError('Markdown Gherkin is not supported');
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

  /// Builds a `source` [messages.Envelope] from raw Gherkin [data].
  ///
  /// The media type is taken from [mediaType] when provided; otherwise it is
  /// inferred from the [uri] extension (`.feature`). When [mediaType]
  /// is omitted and the [uri] has no recognized extension, an [ArgumentError]
  /// is thrown.
  static messages.Envelope makeSourceEnvelope(
    String data,
    String uri, {
    messages.SourceMediaType? mediaType,
  }) {
    final resolvedMediaType = mediaType ?? _inferMediaType(uri);
    return messages.Envelope(
      source: messages.Source(
        uri: uri,
        data: data,
        mediaType: resolvedMediaType,
      ),
    );
  }

  static messages.SourceMediaType _inferMediaType(String uri) {
    if (uri.endsWith('.feature')) {
      return messages.SourceMediaType.textXCucumberGherkinPlain;
    }
    throw ArgumentError(
      'The uri ($uri) must end with .feature, or a mediaType must be '
      'provided',
    );
  }
}
