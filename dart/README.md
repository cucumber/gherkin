# Gherkin for Dart

Gherkin parser and compiler for Dart. Parses `.feature` and Markdown sources into
[Cucumber Messages](https://github.com/cucumber/messages) envelopes: `source`,
`gherkinDocument`, and `pickle`. See [Gherkin](https://github.com/cucumber/gherkin)
for the format and the other language implementations.

The core is platform-agnostic and has no `dart:io` dependency, so it runs on the web.
File reading lives in a separate library.

## Requirements

* Dart SDK `>=3.7.0 <4.0.0`

## Installation

From the Git repository (monorepo subdirectory):

```yaml
dependencies:
  cucumber_gherkin:
    git:
      url: https://github.com/cucumber/gherkin.git
      path: dart
```

When published to [pub.dev](https://pub.dev/packages/cucumber_gherkin), add:

```yaml
dependencies:
  cucumber_gherkin: ^<published-version>
```

Import the platform-agnostic API from the package root:

```dart
import 'package:cucumber_gherkin/cucumber_gherkin.dart';
```

To read Gherkin from files, import the I/O library instead. It re-exports the core
API and adds `dart:io` file entry points:

```dart
import 'package:cucumber_gherkin/cucumber_gherkin_io.dart';
```

Do not import from `package:cucumber_gherkin/src/...`; files under `lib/src/` are
implementation details and may change without notice.

## Parsing

`GherkinParser` turns Gherkin into a `Stream<Envelope>`. Choose an entry point by
where the source lives.

Parse an in-memory string. The media type is inferred from the `uri` extension
(`.feature` or `.md`), or pass `mediaType` when the extension is unrecognized:

```dart
import 'package:cucumber_gherkin/cucumber_gherkin.dart';

final parser = GherkinParser();
final envelopes = parser.parseString(
  'Feature: Minimal\n\n  Scenario: minimalistic\n    Given the minimalism\n',
  'minimal.feature',
);

await for (final envelope in envelopes) {
  // Do something with envelope
}
```

Parse a file (I/O library only). Read is asynchronous, on first listen:

```dart
import 'package:cucumber_gherkin/cucumber_gherkin_io.dart';

final parser = GherkinParser();
final envelopes = await parser.parsePath('example/minimal.feature').toList();
```

Other entry points:

* `parseEnvelope(Envelope)` parses a single `source` envelope.
* `parseEnvelopes(Stream<Envelope>)` parses a stream of `source` envelopes.
* `parsePaths(Iterable<String>)` parses many files (I/O library only).

Streams are lazy across sources, eager within a source: a document is built and
compiled in full the first time its portion of the stream is pulled, and a later
source is not read or parsed until the preceding source's envelopes are consumed.

### Options

`GherkinParser` takes:

* `includeSource`, `includeGherkinDocument`, `includePickles` (all default `true`)
  select which envelope kinds are emitted.
* `defaultDialect` (default `'en'`) sets the dialect used when a feature has no
  `# language:` header.
* `idGenerator` (default `IdGenerator.uuidGenerator`) assigns message ids. Use
  `IdGenerator.incrementingGenerator` for predictable ids in tests.

### Errors

Malformed Gherkin never throws. It is reported as a `parseError` envelope in the
stream. Synchronous throws are reserved for conditions that are not a property of
the source:

* `parseString` and `makeSourceEnvelope` throw `ArgumentError` when the media type
  cannot be resolved (no `mediaType` and an unrecognized `uri` extension).
* `parsePath`/`parsePaths` surface I/O failures as a `GherkinException` error event
  on the stream.

## Development

From the `dart/` directory:

```sh
dart pub get
dart format .
dart analyze
dart test
dart pub publish --dry-run
```

Generated sources:

```sh
make generate                # regenerates lib/src/parser/parser.g.dart (requires berp)
make copy-gherkin-languages  # regenerates dialects from gherkin-languages.json (requires jq)
```

`bin/gherkin.dart` is an internal CLI used by the acceptance tests, not a public
entry point. It reads `source` envelopes as NDJSON from stdin, or reads the file
paths given as arguments, and writes envelopes as NDJSON to stdout:

```sh
dart run bin/gherkin.dart example/minimal.feature
```

Flags: `--no-source`, `--no-ast`, `--no-pickles`, `--predictable-ids`, and
`--default-dialect <lang>`.

## Acceptance test suite

Acceptance tests compare ASTs, pickles, sources, and errors against the fixtures in
`../testdata/`:

```sh
make acceptance
```

For general information about Gherkin and the other language implementations, see the
repository root [README](https://github.com/cucumber/gherkin/blob/main/README.md).
