# Gherkin for Dart

Gherkin parser and compiler for Dart. It parses `.feature` sources into [Cucumber
Messages](https://github.com/cucumber/messages) envelopes (via the
[`cucumber_messages`](https://pub.dev/packages/cucumber_messages) package).

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

Import from the package root:

```dart
import 'package:cucumber_gherkin/cucumber_gherkin.dart';
```

Do not import from `package:cucumber_gherkin/src/...`; files under `lib/src/` are
implementation details and may change without notice.

## Parsing

`generateMessages` turns Gherkin into a `List` of envelopes:

```dart
import 'package:cucumber_gherkin/cucumber_gherkin.dart';

final envelopes = generateMessages(
  'Feature: Minimal\n\n  Scenario: minimalistic\n    Given the minimalism\n',
  'minimal.feature',
  GherkinOptions(
    includeSource: true,
    includeGherkinDocument: true,
    includePickles: true,
    defaultDialect: 'en',
    idGenerator: () => 'fixed-id', // omit for random UUIDs
  ),
);

for (final envelope in envelopes) {
  // source, gherkinDocument, pickle, or parseError
}
```

Malformed Gherkin is reported as a `parseError` envelope, not thrown.

## Development

See the repository root [CONTRIBUTING.md](https://github.com/cucumber/gherkin/blob/main/CONTRIBUTING.md).
From the `dart/` directory:

```sh
dart pub get
dart format .
dart analyze
dart test
make acceptance
dart pub publish --dry-run
```

For general information about Gherkin and the other language implementations, see the
repository root [README](https://github.com/cucumber/gherkin/blob/main/README.md).
