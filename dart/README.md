# Gherkin for Dart

Gherkin parser/compiler for Dart.

The Dart implementation emits [Cucumber Messages](https://github.com/cucumber/messages)
using the [`cucumber_messages`](https://pub.dev/packages/cucumber_messages) package
from pub.dev.

## Library usage

```dart
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:gherkin/gherkin.dart';
import 'package:gherkin/language.dart';

final parser = (GherkinParser.builder()
      ..includeSource = false
      ..idGenerator = IdGenerator.incrementingGenerator)
    .build();

final envelopes = await parser
    .parsePath('../testdata/good/minimal.feature')
    .toList();

final pickle = envelopes
    .map((messages.Envelope envelope) => envelope.pickle)
    .whereType<messages.Pickle>()
    .single;
```

`GherkinParser` can also parse multiple paths (`parsePaths`) or pre-built source
envelopes (`parseEnvelope` / `parseEnvelopes`). Both `.feature` and Markdown
`.feature.md` sources are supported.

## CLI

The CLI reads `.feature`/`.feature.md` files (or NDJSON source envelopes on
stdin) and writes NDJSON messages:

```console
dart run bin/gherkin.dart [options] <paths...>
```

Once the package is activated (`dart pub global activate gherkin`), the same
binary is available as the `gherkin` executable.

Options:

- `--no-source` — omit `source` envelopes
- `--no-ast` — omit `gherkinDocument` envelopes
- `--no-pickles` — omit `pickle` envelopes
- `--predictable-ids` — use incrementing ids instead of UUIDs
- `--default-dialect <lang>` — dialect to use when a feature has no `# language:` header (defaults to `en`)

A second binary emits the tokenized representation used by the acceptance
tests (mirrors `gherkin-generate-tokens` in the other implementations):

```console
dart run bin/gherkin_generate_tokens.dart <paths...>
```

This binary is available as `gherkin-generate-tokens` once the package is
activated.

## Tests

```console
dart test
```

`test/acceptance_test.dart` is a pure-Dart, cross-platform port of the
shared acceptance suite: it compares the AST, pickle, source, and error
output against the reference `../testdata` fixtures (including the Markdown
fixtures). On Linux/macOS CI the same coverage is available via `make acceptance`.
