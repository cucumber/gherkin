# Gherkin for Dart

Gherkin parser/compiler for Dart. Parses `.feature` and Markdown `.feature.md`
sources into [Cucumber Messages](https://github.com/cucumber/messages).

This package builds on the [`cucumber_messages`](https://pub.dev/packages/cucumber_messages)
package for the message types it emits.

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

The package has two public libraries:

- `package:cucumber_gherkin/cucumber_gherkin.dart` — the core, **platform-agnostic**
  API (no `dart:io`, so it works on the web). Exposes `GherkinParser`,
  `IdGenerator`, `GherkinDialect`/`GherkinDialectProvider`,
  `GherkinLanguageKeywords`, and the `GherkinException` hierarchy. Feed Gherkin
  in via `parseString`, `parseEnvelope`, or `parseEnvelopes`.
- `package:cucumber_gherkin/cucumber_gherkin_io.dart` — re-exports the core and
  adds the `dart:io`-based file entry points `parsePath`/`parsePaths` as
  extension methods on `GherkinParser`. Import this on the Dart VM, Flutter
  mobile/desktop, or server-side.

```dart
// Web / platform-agnostic:
import 'package:cucumber_gherkin/cucumber_gherkin.dart';

// When you also need to read from files:
import 'package:cucumber_gherkin/cucumber_gherkin_io.dart';
```

Do not import from `package:cucumber_gherkin/src/...`; files under `lib/src/`
are implementation details and may change without notice.

The parser emits `cucumber_messages` types. Import that package alongside this
one when you need to inspect envelopes:

```dart
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
```

## Parsing

`GherkinParser` parses files, in-memory strings, or pre-built source envelopes,
and emits a stream of `Envelope`s.

> **Error handling contract:** malformed Gherkin never throws — it is reported
> as a `parseError` envelope in the stream. The only synchronous throws are for
> conditions that are *not* a property of the Gherkin source:
>
> - I/O failures from the file-reading entry points (`parsePath` /
>   `parsePaths`) are thrown as a `GherkinException`. This matches the flagship
>   implementations (e.g. Java's `parse(Path)` declares `throws IOException`).
> - `parseString` (and `GherkinParser.makeSourceEnvelope`) throw an
>   `ArgumentError` when the media type cannot be resolved — that is, when
>   `mediaType` is omitted and the `uri` has no recognized extension
>   (`.feature` or `.md`). This is detected before any parsing begins, so it is
>   surfaced synchronously rather than as a `parseError` envelope. Pass
>   `mediaType` explicitly to avoid it.

```dart
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:cucumber_gherkin/cucumber_gherkin_io.dart';

final parser = GherkinParser();

final envelopes = await parser
    .parsePath('example/minimal.feature')
    .toList();

final pickle = envelopes
    .map((messages.Envelope envelope) => envelope.pickle)
    .whereType<messages.Pickle>()
    .single;
```

Entry points:

- `parsePath(path)` / `parsePaths(paths)` (from
  `cucumber_gherkin_io.dart`): read files. I/O failures throw a
  `GherkinException`; malformed Gherkin is reported as a `parseError` envelope.
- `parseString(data, uri, {mediaType})`: parse in-memory Gherkin. `uri`
  supplies the source reference. The media type is taken from `mediaType` when
  given; otherwise it is inferred from the `uri` extension (`.feature` or
  `.md`). Pass `mediaType` when the `uri` has no recognized extension.
- `parseEnvelope(envelope)` / `parseEnvelopes(stream)`: parse pre-built
  `source` envelopes.

### Configuration

Configure which envelope kinds are emitted, the fallback dialect, and id
generation via named constructor arguments. All envelope kinds are emitted by
default; ids default to UUIDs.

```dart
final parser = GherkinParser(
  includeSource: false,
  defaultDialect: 'en',
  idGenerator: IdGenerator.incrementingGenerator,
);
```

`IdGenerator.uuidGenerator` produces random v4 UUIDs (the default).
`IdGenerator.incrementingGenerator` produces predictable sequential ids
starting at `0`.

### Dialects

`GherkinDialectProvider` and `GherkinDialect` (exported from
`package:cucumber_gherkin/cucumber_gherkin.dart`) expose the supported languages
and their localized keywords. A feature selects its dialect
with a `# language:` header; `defaultDialect` (default `en`) applies when the
header is absent. Requesting an unsupported language throws a
`NoSuchLanguageException`.

See the tests under [`test/`](test/) for more usage.

## Development

From the `dart/` directory:

```sh
make copy-gherkin-languages   # copy ../gherkin-languages.json and generate dialects
make generate                 # requires berp (.NET tool); regenerates the parser from ../gherkin.berp
dart pub get
dart format .
dart analyze
dart test
dart pub publish --dry-run
```

`make generate` runs `berp` against `gherkin-dart.razor` and `../gherkin.berp`
to produce `lib/src/parser/parser.g.dart`. Install berp with
`dotnet tool update Berp --version 1.6.0 --tool-path ~/bin`.

## Acceptance Test Suite

`test/acceptance/gherkin_acceptance_test.dart` is a pure-Dart, cross-platform port of the shared
acceptance suite. It reads fixtures from `../testdata/` in the monorepo and
compares AST, pickle, source, and error output against the reference (including
the Markdown fixtures). Run it with `dart test` alongside the unit tests.

On Linux/macOS the same coverage is available via `make acceptance`, which
shells out to `bash`/`jq`/`diff`. Acceptance output under `acceptance/` and the
monorepo fixtures are not part of the published package.

For general information about Gherkin and the other language implementations,
see the repository root [README](../README.md).
