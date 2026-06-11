import 'dart:io';

import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:gherkin/exceptions.dart';
import 'package:gherkin/language.dart' as lang;
import 'package:gherkin/parser.dart';
import 'package:gherkin/src/ast/messages_gherkin_document_builder.dart';
import 'package:gherkin/src/pickles/messages_pickle_compiler.dart';

class GherkinParser {
  final bool includeSource;
  final bool includeGherkinDocument;
  final bool includePickles;
  final String defaultDialect;
  final lang.IdGenerator idGenerator;

  late final lang.IGherkinDialectProvider _dialectProvider;

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

  static GherkinParserBuilder builder() => GherkinParserBuilder();

  Stream<messages.Envelope> parsePath(String path) {
    try {
      // Normalize CRLF → LF so source data is consistent across platforms and
      // matches the line-feed-only reference fixtures.
      final data = File(
        path,
      ).readAsStringSync().replaceAll('\r\n', '\n').replaceAll('\r', '\n');
      return parseEnvelope(makeSourceEnvelope(data, path));
    } on IOException catch (e) {
      throw GherkinException(e.toString(), e);
    }
  }

  Stream<messages.Envelope> parsePaths(Iterable<String> paths) {
    return Stream.fromIterable(paths).asyncExpand(parsePath);
  }

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

class GherkinParserBuilder {
  bool _includeSource = true;
  bool _includeGherkinDocument = true;
  bool _includePickles = true;
  String _defaultDialect = 'en';
  lang.IdGenerator _idGenerator = lang.IdGenerator.uuidGenerator;

  GherkinParserBuilder includeSource(bool includeSource) {
    _includeSource = includeSource;
    return this;
  }

  GherkinParserBuilder includeGherkinDocument(bool includeGherkinDocument) {
    _includeGherkinDocument = includeGherkinDocument;
    return this;
  }

  GherkinParserBuilder includePickles(bool includePickles) {
    _includePickles = includePickles;
    return this;
  }

  GherkinParserBuilder defaultDialect(String defaultDialect) {
    _defaultDialect = defaultDialect;
    return this;
  }

  GherkinParserBuilder idGenerator(lang.IdGenerator idGenerator) {
    _idGenerator = idGenerator;
    return this;
  }

  GherkinParser build() => GherkinParser(
    includeSource: _includeSource,
    includeGherkinDocument: _includeGherkinDocument,
    includePickles: _includePickles,
    defaultDialect: _defaultDialect,
    idGenerator: _idGenerator,
  );
}

class Gherkin {
  static Stream<messages.Envelope> fromPaths(
    List<String> paths,
    bool includeSource,
    bool includeAst,
    bool includePickles,
    lang.IdGenerator idGenerator,
  ) {
    return GherkinParser(
      includeSource: includeSource,
      includeGherkinDocument: includeAst,
      includePickles: includePickles,
      idGenerator: idGenerator,
    ).parsePaths(paths);
  }

  static Stream<messages.Envelope> fromSources(
    List<messages.Envelope> envelopes,
    bool includeSource,
    bool includeAst,
    bool includePickles,
    lang.IdGenerator idGenerator,
  ) {
    return GherkinParser(
      includeSource: includeSource,
      includeGherkinDocument: includeAst,
      includePickles: includePickles,
      idGenerator: idGenerator,
    ).parseEnvelopes(Stream.fromIterable(envelopes));
  }

  static messages.Envelope makeSourceEnvelope(String data, String uri) =>
      GherkinParser.makeSourceEnvelope(data, uri);
}
