import 'dart:io';

import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:gherkin/exceptions.dart';
import 'package:gherkin/language.dart' as lang;
import 'package:gherkin/parser.dart';
import 'package:gherkin/src/ast/messages_gherkin_document_builder.dart';
import 'package:gherkin/src/pickles/messages_pickle_compiler.dart';

/// Parses Gherkin documents into a stream of Cucumber [messages.Envelope]s.
class GherkinParser {
  /// Creates a parser.
  ///
  /// Use [includeSource], [includeGherkinDocument], and [includePickles] to
  /// control which kinds of envelopes are emitted, [defaultDialect] to choose
  /// the dialect used when a feature has no `# language:` header, and
  /// [idGenerator] to assign message ids (defaults to UUIDs).
  GherkinParser({
    this.includeSource = true,
    this.includeGherkinDocument = true,
    this.includePickles = true,
    this.defaultDialect = 'en',
    lang.IdGenerator? idGenerator,
  }) : idGenerator = idGenerator ?? lang.IdGenerator.uuidGenerator {
    final languages = lang.loadGherkinLanguagesFromJsonAsset();
    _dialectProvider = lang.GherkinDialectProvider(languages, defaultDialect);
  }

  /// Whether `source` envelopes are emitted.
  final bool includeSource;

  /// Whether `gherkinDocument` envelopes are emitted.
  final bool includeGherkinDocument;

  /// Whether `pickle` envelopes are emitted.
  final bool includePickles;

  /// The dialect used when a feature has no `# language:` header.
  final String defaultDialect;

  /// The [lang.IdGenerator] used to assign ids to emitted messages.
  final lang.IdGenerator idGenerator;

  late final lang.IGherkinDialectProvider _dialectProvider;

  /// Creates a [GherkinParserBuilder] for fluent configuration.
  static GherkinParserBuilder builder() => GherkinParserBuilder();

  /// Parses the file at [path] and emits the resulting envelopes.
  Stream<messages.Envelope> parsePath(String path) {
    try {
      // Read the file verbatim. The `source` envelope's `data` must preserve
      // the original bytes (including CRLF), matching the other first-party
      // implementations (e.g. Go sets `Data: string(in)`); the line scanner
      // tolerates CRLF when classifying tokens.
      final data = File(path).readAsStringSync();
      return parseEnvelope(makeSourceEnvelope(data, path));
    } on IOException catch (e) {
      throw GherkinException(e.toString(), e);
    }
  }

  /// Parses each path in [paths] and emits the resulting envelopes.
  Stream<messages.Envelope> parsePaths(Iterable<String> paths) {
    return Stream.fromIterable(paths).asyncExpand(parsePath);
  }

  /// Parses a single source [envelope] and emits the resulting envelopes.
  ///
  /// The incoming [envelope] is re-emitted first when [includeSource] is set.
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

  /// Parses a stream of source [envelopes] and emits the resulting envelopes.
  Stream<messages.Envelope> parseEnvelopes(
    Stream<messages.Envelope> envelopes,
  ) {
    return envelopes.asyncExpand(parseEnvelope);
  }

  List<messages.Envelope> _parseSource(messages.Source source) {
    final result = <messages.Envelope>[];
    if (!includeGherkinDocument && !includePickles) {
      return result;
    }

    final builder = MessagesGherkinDocumentBuilder(idGenerator);
    final parser = Parser<messages.GherkinDocument>(builder)
      ..stopAtFirstError = false;
    final tokenMatcher = _tokenMatcher(source.mediaType);
    final tokenScanner = lang.StringTokenScanner(source.data);

    try {
      final gherkinDocument = parser.parse(tokenScanner, tokenMatcher);
      final gherkinDocumentWithUri = messages.GherkinDocument(
        uri: source.uri,
        feature: gherkinDocument.feature,
        comments: gherkinDocument.comments,
      );

      if (includeGherkinDocument) {
        result.add(messages.Envelope(gherkinDocument: gherkinDocumentWithUri));
      }
      if (includePickles) {
        final pickleCompiler = MessagesPickleCompiler(idGenerator);
        for (final pickle in pickleCompiler.compile(
          gherkinDocumentWithUri,
          source.uri,
        )) {
          result.add(messages.Envelope(pickle: pickle));
        }
      }
    } on CompositeParserException catch (e) {
      for (final error in e.errors) {
        result.add(_parseErrorEnvelope(error, source.uri));
      }
    } on ParserException catch (e) {
      result.add(_parseErrorEnvelope(e, source.uri));
    }

    return result;
  }

  ITokenMatcher _tokenMatcher(messages.SourceMediaType mediaType) {
    switch (mediaType) {
      case messages.SourceMediaType.textXCucumberGherkinPlain:
        return lang.TokenMatcher(_dialectProvider);
      case messages.SourceMediaType.textXCucumberGherkinMarkdown:
        return lang.MarkdownTokenMatcher(_dialectProvider, defaultDialect);
    }
  }

  messages.Envelope _parseErrorEnvelope(ParserException error, String uri) {
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
  /// The media type is inferred from the [uri] extension (`.feature` or `.md`);
  /// any other extension throws an [ArgumentError].
  static messages.Envelope makeSourceEnvelope(String data, String uri) {
    messages.SourceMediaType mediaType;
    if (uri.endsWith('.feature')) {
      mediaType = messages.SourceMediaType.textXCucumberGherkinPlain;
    } else if (uri.endsWith('.md')) {
      mediaType = messages.SourceMediaType.textXCucumberGherkinMarkdown;
    } else {
      throw ArgumentError('The uri ($uri) must end with .feature or .md');
    }
    return messages.Envelope(
      source: messages.Source(uri: uri, data: data, mediaType: mediaType),
    );
  }
}

/// A mutable builder for configuring and creating a [GherkinParser].
///
/// Configure the builder with cascades and then call [build]:
///
/// ```dart
/// final parser = (GherkinParser.builder()
///       ..includeSource = false
///       ..idGenerator = IdGenerator.incrementingGenerator)
///     .build();
/// ```
class GherkinParserBuilder {
  /// Whether the built parser should emit `source` envelopes.
  bool includeSource = true;

  /// Whether the built parser should emit `gherkinDocument` envelopes.
  bool includeGherkinDocument = true;

  /// Whether the built parser should emit `pickle` envelopes.
  bool includePickles = true;

  /// The dialect used when a feature has no `# language:` header.
  String defaultDialect = 'en';

  /// The [lang.IdGenerator] used to assign ids to emitted messages.
  lang.IdGenerator idGenerator = lang.IdGenerator.uuidGenerator;

  /// Creates a [GherkinParser] using the current configuration.
  GherkinParser build() => GherkinParser(
    includeSource: includeSource,
    includeGherkinDocument: includeGherkinDocument,
    includePickles: includePickles,
    defaultDialect: defaultDialect,
    idGenerator: idGenerator,
  );
}

/// Convenience entry points for parsing Gherkin into Cucumber Messages.
class Gherkin {
  /// Parses each path in [paths] and emits the resulting [messages.Envelope]s.
  ///
  /// Use [includeSource], [includeGherkinDocument], and [includePickles] to
  /// control which kinds of envelopes are emitted, and [idGenerator] to assign
  /// message ids (defaults to UUIDs). All envelope kinds are emitted by
  /// default.
  static Stream<messages.Envelope> fromPaths(
    List<String> paths, {
    bool includeSource = true,
    bool includeGherkinDocument = true,
    bool includePickles = true,
    lang.IdGenerator? idGenerator,
  }) {
    return GherkinParser(
      includeSource: includeSource,
      includeGherkinDocument: includeGherkinDocument,
      includePickles: includePickles,
      idGenerator: idGenerator,
    ).parsePaths(paths);
  }

  /// Parses the source [envelopes] and emits the resulting
  /// [messages.Envelope]s.
  ///
  /// Use [includeSource], [includeGherkinDocument], and [includePickles] to
  /// control which kinds of envelopes are emitted, and [idGenerator] to assign
  /// message ids (defaults to UUIDs). All envelope kinds are emitted by
  /// default.
  static Stream<messages.Envelope> fromSources(
    List<messages.Envelope> envelopes, {
    bool includeSource = true,
    bool includeGherkinDocument = true,
    bool includePickles = true,
    lang.IdGenerator? idGenerator,
  }) {
    return GherkinParser(
      includeSource: includeSource,
      includeGherkinDocument: includeGherkinDocument,
      includePickles: includePickles,
      idGenerator: idGenerator,
    ).parseEnvelopes(Stream.fromIterable(envelopes));
  }

  /// Builds a `source` [messages.Envelope] from raw Gherkin [data].
  ///
  /// The media type is inferred from the [uri] extension (`.feature` or `.md`).
  static messages.Envelope makeSourceEnvelope(String data, String uri) =>
      GherkinParser.makeSourceEnvelope(data, uri);
}
