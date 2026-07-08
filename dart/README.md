# Gherkin for Dart

Gherkin parser and compiler for Dart. Parses `.feature` sources into [Cucumber
Messages](https://github.com/cucumber/messages) envelopes: `source`,
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

`GherkinParser` turns Gherkin into a `Stream<Envelope>`. The media type is inferred
from the `uri` extension (`.feature`), or pass `mediaType` when the extension is
unrecognized:

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

Other entry points: `parseEnvelope`/`parseEnvelopes` parse `source` envelopes, and
(in the I/O library) `parsePath`/`parsePaths` read files. Streams are lazy across
sources but eager within a source. `GherkinParser` accepts `includeSource`,
`includeGherkinDocument`, `includePickles`, `defaultDialect`, and `idGenerator`.

### Errors

Malformed Gherkin never throws. It is reported as a `parseError` envelope in the
stream. Synchronous throws are reserved for conditions that are not a property of
the source:

* `parseString` and `makeSourceEnvelope` throw `ArgumentError` when the media type
  cannot be resolved (no `mediaType` and an unrecognized `uri` extension).
* `parsePath`/`parsePaths` surface I/O failures as a `GherkinException` error event
  on the stream.

## Development

See the repository root [CONTRIBUTING.md](https://github.com/cucumber/gherkin/blob/main/CONTRIBUTING.md).
From the `dart/` directory:

```sh
dart pub get
dart format .
dart analyze
dart test
dart pub publish --dry-run
```

For general information about Gherkin and the other language implementations, see the
repository root [README](https://github.com/cucumber/gherkin/blob/main/README.md).
