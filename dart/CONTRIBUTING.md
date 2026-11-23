# Contributing to Gherkin for Dart

Read the repository root [CONTRIBUTING.md](../CONTRIBUTING.md) before making a
change.

## Setup

Install the supported [Dart SDK](https://dart.dev/get-dart) and fetch the
package dependencies from this directory:

```sh
dart pub get
```

## Verification

Run these commands from the `dart/` directory before opening a pull request:

```sh
dart format --output=none --set-exit-if-changed .
dart analyze
dart test
make acceptance
dart pub publish --dry-run
```

## Coverage

Install the same coverage tool version as CI, then run both suites:

```sh
dart pub global activate coverage 1.15.0
make coverage
```

This removes previous coverage and acceptance outputs to force fresh execution.
The existing token, AST, pickle, source, and error comparisons still run.
Raw reports are stored in `coverage/unit/` and `coverage/acceptance/`;
`coverage/lcov.info` combines both suites and honors the existing generated-file
exclusions. The 99.8% threshold applies to the combined report.

The coverage target requires Bash, Make, and jq (on Windows, use Git Bash with
Make and jq on PATH). `make acceptance` remains available without instrumentation.

## Generated Sources

The parser and dialect definitions are generated sources. Regenerate them after
changing their inputs:

```sh
make generate
make copy-gherkin-languages
```
