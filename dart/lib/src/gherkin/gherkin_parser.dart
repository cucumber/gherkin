import 'package:cucumber_gherkin/src/ast/messages_gherkin_document_builder.dart';
import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/gherkin/id_generator.dart';
import 'package:cucumber_gherkin/src/language/dialects_builtin.g.dart';
import 'package:cucumber_gherkin/src/language/gherkin_dialect_provider.dart';
import 'package:cucumber_gherkin/src/language/gherkin_token_matcher.dart';
import 'package:cucumber_gherkin/src/language/markdown_token_matcher.dart';
import 'package:cucumber_gherkin/src/language/string_token_scanner.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_gherkin/src/parser/token_matcher.dart';
import 'package:cucumber_gherkin/src/pickles/messages_pickle_compiler.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// Parses Gherkin documents into a stream of Cucumber [messages.Envelope]s.
///
/// ## Streaming semantics
///
/// The returned [Stream]s are lazy across sources but eager within a source.
/// Each source (file, string, or `source` envelope) is parsed in full the first
/// time its portion of the stream is pulled: a Gherkin document is not
/// available incrementally, since building the AST and compiling pickles needs
/// the whole document. When several sources are parsed together (for example
/// via [parseEnvelopes], or `parsePaths` from
/// `package:cucumber_gherkin/cucumber_gherkin_io.dart`), a later source is not
/// read or parsed until the preceding source's envelopes are consumed.
///
/// The file-reading entry points (`parsePath`/`parsePaths`) live in the
/// separate `package:cucumber_gherkin/cucumber_gherkin_io.dart` library because
/// they depend on `dart:io`. This core library stays platform-agnostic and
/// usable on the web.
///
/// ## Error contract
///
/// Malformed Gherkin never throws. It is reported as a `parseError` envelope in
/// the stream. The only synchronous throws are for conditions that are not a
/// property of the Gherkin source and are detected before parsing:
///
/// * [parseString] and [makeSourceEnvelope] throw an [ArgumentError] when the
///   media type cannot be resolved (no `mediaType` and an unrecognized `uri`
///   extension);
/// * the file-reading entry points (`parsePath`/`parsePaths`) surface I/O
///   failures as a [GherkinException] error event on the stream.
class GherkinParser {
  /// Creates a parser.
  ///
  /// Use [includeSource], [includeGherkinDocument], and [includePickles] to
  /// control which kinds of envelopes are emitted, [defaultDialect] to choose
  /// the dialect used when a feature has no `# language:` header, and
  /// [idGenerator] to assign message ids (defaults to UUIDs).
  GherkinParser({
    this.includeSource = defaultIncludeSource,
    this.includeGherkinDocument = defaultIncludeGherkinDocument,
    this.includePickles = defaultIncludePickles,
    this.defaultDialect = defaultDialectValue,
    IdGenerator? idGenerator,
  }) : idGenerator = idGenerator ?? IdGenerator.uuidGenerator {
    // Dialects are embedded as generated Dart source in
    // `dialects_builtin.g.dart` (from `gherkin-languages.json`), so loading
    // does not depend on the working directory, runtime asset resolution, or
    // package layout.
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

  /// Parses in-memory Gherkin [data] identified by [uri] and emits the
  /// resulting envelopes.
  ///
  /// The [uri] is used as the source reference; it does not need to point at a
  /// real file. No I/O is performed. To read Gherkin from a file, use
  /// `parsePath` from `package:cucumber_gherkin/cucumber_gherkin_io.dart`.
  ///
  /// The media type is taken from [mediaType] when provided; otherwise it is
  /// inferred from the [uri] extension (`.feature` or `.md`). Pass [mediaType]
  /// explicitly when the [uri] has no recognized extension.
  ///
  /// Unlike malformed Gherkin, which is always reported as a `parseError`
  /// envelope and never thrown, this method throws an [ArgumentError]
  /// synchronously when [mediaType] is omitted and the [uri] has no recognized
  /// extension: the media type cannot be resolved before parsing begins.
  Stream<messages.Envelope> parseString(
    String data,
    String uri, {
    messages.SourceMediaType? mediaType,
  }) {
    return parseEnvelope(makeSourceEnvelope(data, uri, mediaType: mediaType));
  }

  /// Parses a single source [envelope] and emits the resulting envelopes.
  ///
  /// The incoming [envelope] is re-emitted first when [includeSource] is set.
  ///
  /// The source is parsed in full when the first `gherkinDocument`/`pickle`
  /// envelope is pulled from the stream (see the class-level streaming
  /// semantics); the document cannot be produced incrementally.
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
      // Build the token matcher inside the try. Constructing it resolves the
      // default dialect eagerly, so an unsupported `defaultDialect` (no
      // `# language:` header, hence no location) must surface as a `parseError`
      // envelope rather than escape to the caller.
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
        return MarkdownTokenMatcher(_dialectProvider, defaultDialect);
    }
  }

  messages.Envelope _parseErrorEnvelope(ParserException error, String uri) {
    // A location-less error (e.g. an unsupported default dialect) has no
    // position to report. Emit a null location and the "(-1,0)" prefix used by
    // the other first-party implementations (see Java's ParserException).
    if (error.location.isEmpty) {
      return messages.Envelope(
        parseError: messages.ParseError(
          source: messages.SourceReference(uri: uri),
          message: '(-1,0): ${error.message}',
        ),
      );
    }

    final line = error.location.line;
    final column = error.location.column;
    // Prefix the message with "(line:column): " to match the format produced
    // by the other first-party Gherkin implementations.
    final prefix = '($line:$column): ';
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
        message: '$prefix${error.message}',
      ),
    );
  }

  /// Builds a `source` [messages.Envelope] from raw Gherkin [data].
  ///
  /// The media type is taken from [mediaType] when provided; otherwise it is
  /// inferred from the [uri] extension (`.feature` or `.md`). When [mediaType]
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
    if (uri.endsWith('.md')) {
      return messages.SourceMediaType.textXCucumberGherkinMarkdown;
    }
    throw ArgumentError(
      'The uri ($uri) must end with .feature or .md, or a mediaType must be '
      'provided',
    );
  }
}
