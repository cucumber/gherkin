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

## Generated Sources

The parser and dialect definitions are generated sources. Regenerate them after
changing their inputs:

```sh
make generate
make copy-gherkin-languages
```
