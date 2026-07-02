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

Import the public API from the package libraries:

```dart
import 'package:cucumber_gherkin/gherkin.dart';      // GherkinParser, Gherkin, IdGenerator
import 'package:cucumber_gherkin/language.dart';     // GherkinDialect, GherkinDialectProvider
import 'package:cucumber_gherkin/exceptions.dart';   // GherkinException and subtypes
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

```dart
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:cucumber_gherkin/gherkin.dart';

final parser = GherkinParser();

final envelopes = await parser
    .parsePath('../testdata/good/minimal.feature')
    .toList();

final pickle = envelopes
    .map((messages.Envelope envelope) => envelope.pickle)
    .whereType<messages.Pickle>()
    .single;
```

Entry points:

- `parsePath(path)` / `parsePaths(paths)`: read files. I/O failures throw a
  `GherkinException`; malformed Gherkin is reported as a `parseError` envelope.
- `parseString(data, uri)`: parse in-memory Gherkin. `uri` supplies the source
  reference and infers the media type from its extension (`.feature` or `.md`).
- `parseEnvelope(envelope)` / `parseEnvelopes(stream)`: parse pre-built
  `source` envelopes.

### Configuration

Configure which envelope kinds are emitted, the fallback dialect, and id
generation. All envelope kinds are emitted by default; ids default to UUIDs.

Use the constructor:

```dart
final parser = GherkinParser(
  includeSource: false,
  defaultDialect: 'en',
  idGenerator: IdGenerator.incrementingGenerator,
);
```

Or the builder:

```dart
final parser = (GherkinParser.builder()
      ..includeSource = false
      ..idGenerator = IdGenerator.incrementingGenerator)
    .build();
```

`IdGenerator.uuidGenerator` produces random v4 UUIDs (the default).
`IdGenerator.incrementingGenerator` produces predictable sequential ids
starting at `0`.

The static `Gherkin` helpers wrap a one-shot parser:
`Gherkin.fromPaths(...)`, `Gherkin.fromString(...)`, `Gherkin.fromSources(...)`.

### Dialects

`GherkinDialectProvider` and `GherkinDialect` (in `language.dart`) expose the
supported languages and their localized keywords. A feature selects its dialect
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

`test/acceptance_test.dart` is a pure-Dart, cross-platform port of the shared
acceptance suite. It reads fixtures from `../testdata/` in the monorepo and
compares AST, pickle, source, and error output against the reference (including
the Markdown fixtures). Run it with `dart test` alongside the unit tests.

On Linux/macOS the same coverage is available via `make acceptance`, which
shells out to `bash`/`jq`/`diff`. Acceptance output under `acceptance/` and the
monorepo fixtures are not part of the published package.

For general information about Gherkin and the other language implementations,
see the repository root [README](../README.md).
