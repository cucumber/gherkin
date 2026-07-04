import 'package:cucumber_gherkin/cucumber_gherkin_io.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

/// Verifies the error-handling contract shared with the flagship
/// implementations:
///
/// * malformed Gherkin input is reported as a `parseError` envelope and never
///   escapes as a thrown exception;
/// * I/O failures (missing files) are thrown, not enveloped;
/// * an unsupported dialect is reported as a `parseError` envelope, including
///   the location-less default-dialect case.
void main() {
  final idGenerator = IdGenerator.incrementingGenerator;

  GherkinParser parser() => GherkinParser(
    includeSource: false,
    includePickles: false,
    idGenerator: idGenerator,
  );

  Future<List<messages.Envelope>> parseSource(String data, String uri) {
    return parser()
        .parseEnvelope(GherkinParser.makeSourceEnvelope(data, uri))
        .toList();
  }

  group('malformed input produces parseError envelopes (never throws)', () {
    test('unexpected token', () async {
      final envelopes = await parseSource('not gherkin', 'bad.feature');

      expect(envelopes, hasLength(1));
      final parseError = envelopes.single.parseError;
      expect(parseError, isNotNull);
      expect(parseError!.message, contains('expected'));
      expect(parseError.source.location!.line, 1);
    });

    test('unsupported dialect via # language header', () async {
      final envelopes = await parseSource(
        '#language:no-such\nFeature: x\n',
        'bad.feature',
      );

      expect(envelopes, hasLength(1));
      final parseError = envelopes.single.parseError;
      expect(parseError, isNotNull);
      expect(parseError!.message, contains('Language not supported: no-such'));
      // The unsupported-language token carries a real location.
      expect(parseError.source.location!.line, 1);
      expect(parseError.source.location!.column, 1);
    });

    test('multiple errors are all reported as parseError envelopes', () async {
      // Disable the gherkin document so a successful parse would emit only
      // pickles; a failed parse emits only parseError envelopes.
      final envelopes =
          await GherkinParser(
                includeSource: false,
                includeGherkinDocument: false,
                idGenerator: idGenerator,
              )
              .parseEnvelope(
                GherkinParser.makeSourceEnvelope(
                  'invalid line 1\ninvalid line 2\n',
                  'bad.feature',
                ),
              )
              .toList();

      expect(envelopes, isNotEmpty);
      expect(
        envelopes.every((e) => e.parseError != null),
        isTrue,
        reason: 'every emitted envelope should be a parseError',
      );
    });
  });

  group('unsupported-dialect error is always a catchable ParserException', () {
    test('NoSuchLanguageException is a ParserException', () {
      // Being a ParserException is what guarantees the top-level parser
      // catches it and converts it to a parseError envelope instead of letting
      // it escape to the caller.
      expect(NoSuchLanguageException('xx'), isA<ParserException>());
    });

    test(
      'a location-less NoSuchLanguageException stringifies to its message',
      () {
        // With no location, the message must not carry a bogus "(line:column)".
        expect(
          NoSuchLanguageException('xx').toString(),
          'Language not supported: xx',
        );
      },
    );

    test(
      'NoSuchLanguageException accepts an empty language without throwing',
      () {
        // Previously this threw an ArgumentError, which would have escaped the
        // parser's ParserException handling and crashed the caller.
        expect(() => NoSuchLanguageException(''), returnsNormally);
      },
    );
  });

  group('I/O errors are thrown, not enveloped', () {
    test('parsePath on a missing file throws GherkinException', () async {
      // parsePath reads the file asynchronously, so the I/O failure surfaces as
      // an error event on the stream (awaited here) rather than a synchronous
      // throw from the call itself.
      await expectLater(
        parser().parsePath('does-not-exist.feature').toList(),
        throwsA(isA<GherkinException>()),
      );
    });
  });

  group('parseError message formatting', () {
    test('a located error is prefixed with "(line:column): "', () async {
      final envelopes = await parseSource('not gherkin', 'bad.feature');

      final parseError = envelopes.single.parseError!;
      // The location in the prefix must agree with the structured location on
      // the source reference.
      expect(parseError.message, startsWith('(1:1): '));
      expect(parseError.source.location!.line, 1);
      expect(parseError.source.location!.column, 1);
    });

    test(
      'a location-less error uses the "(-1,0): " prefix and omits the location',
      () async {
        // An unsupported *default* dialect (no `# language:` header) has no
        // position to report: it exercises the empty-location branch, which
        // emits the "(-1,0): " prefix and a source reference with no location.
        final envelopes =
            await GherkinParser(
                  includeSource: false,
                  includePickles: false,
                  defaultDialect: 'no-such-lang',
                  idGenerator: idGenerator,
                )
                .parseEnvelope(
                  GherkinParser.makeSourceEnvelope(
                    'Feature: x\n',
                    'bad.feature',
                  ),
                )
                .toList();

        expect(envelopes, isNotEmpty);
        final parseError = envelopes
            .map((e) => e.parseError)
            .whereType<messages.ParseError>()
            .firstWhere((pe) => pe.message.contains('Language not supported'));
        expect(parseError.message, startsWith('(-1,0): '));
        expect(
          parseError.message,
          contains('Language not supported: no-such-lang'),
        );
        expect(parseError.source.location, isNull);
      },
    );
  });

  group('GherkinException', () {
    test('formats without a cause', () {
      expect(GherkinException('boom').toString(), 'boom');
    });

    test('formats with a cause', () {
      const cause = FormatException('bad');
      expect(GherkinException('boom', cause).toString(), 'boom: $cause');
    });
  });
}
